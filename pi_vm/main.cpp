
#include "computer/Computer.h"
#include "ControllerInterface.h"
#include "ProgramArgumentProcessing.h"
#include "programmer/Programmer.h"
#include "computer/architecture/Bit8.h"
#include <thread>
#include <unordered_map>


ComputerArchitecture* getArchitecture(int architecture)
{
    if(architecture==8)
    {
        return new Bit8;
    }
    else if(architecture==4)
    {
        return new Bit4;
    }
    throw std::invalid_argument("The "+std::to_string(architecture)+"-bit architecture is not supported.");
}

void debugCycle(std::unordered_map<int,int>& breakpoints, Computer& unit)
{
    auto breakpoint = breakpoints.find(unit.getRegister(Processor<uint32_t>::PROGRAM_COUNTER));
    std::cout<<"Debugger: Breakpoint hit at "+std::to_string(breakpoint->first)<<std::endl;
    std::cout<<"Type: 'x <address>' to see value of a register or a memory address."<<std::endl;
    std::cout<<"Type: 'b <address>' to add a breakpoint."<<std::endl;
    std::cout<<"Type: 'f' to see all flags."<<std::endl;
    std::cout<<"Type: 'n' to proceed to the next instruction."<<std::endl;
    std::cout<<"Type: 'xr' to see values of all registers."<<std::endl;
    std::cout<<"Type: 'c' to continue execution."<<std::endl;
    while(true)
    {
        if(!unit.isStopped())
        {
            std::string command;
            std::cin>>command;
            if(command == "x")
            {
                int address;
                std::cin>>address;
                int value;
                if(address<unit.getRegistryCount())
                {
                    value = unit.getRegister(address);
                }
                else
                {
                    value = unit.getMemory(address);
                }
                std::cout << "Value: " << std::dec<<value;
                std::cout<<" 0x"<<std::hex<< value;
                std::cout<<" " <<(char)value<<std::endl;
            }
            else if(command =="b")
            {
                int address;
                std::cin>>address;
                breakpoints.insert({address, 0});
                std::cout<<"Breakpoint added!"<<std::endl;
            }
            else if(command =="f")
            {
                for(int i=0;i<FLAG_COUNT;i++)
                {
                    bool value = unit.getFlag(i);
                    std::cout<<"Value of flag "<<i<<": ";
                    std::cout << value <<std::endl;

                }
            }
            else if(command == "n")
            {
                unit.cycle();
                std::cout<<"Debugger: Stopped at "+std::to_string(unit.getRegister(Processor<uint32_t>::PROGRAM_COUNTER))<<std::endl;
            }
            else if(command == "xr")
            {
                for(int i=0;i<unit.getRegistryCount();i++)
                {
                    int value = unit.getRegister(i);
                    std::cout<<"Value of registry "<<i<<": ";
                    std::cout << std::dec<<value;
                    std::cout<<" 0x"<<std::hex<< value;
                    std::cout<<" " <<(char)value<<std::endl;
                }
            }
            else if(command== "c")
            {
                unit.cycle();
                break;
            }
        }
    }

}

void run(Computer& unit, bool debug)
{
    if(debug)
    {
        std::unordered_map<int, int>breakpoints;
        breakpoints.insert({unit.getRegister(Processor<uint32_t>::PROGRAM_COUNTER), 0});
        while(true)
        {
            auto breakpoint = breakpoints.find(unit.getRegister(Processor<uint32_t>::PROGRAM_COUNTER));
            if(breakpoint==breakpoints.end())
            {
                unit.cycle();
            }
            else
            {
                debugCycle(breakpoints, unit);
            }
        }
    }
    else
    {
        while(true)
        {
            unit.cycle();
        }
    }
}

int main(int argc, char* argv[]) {

    try
    {
        ExecutableFileType fileType;
        std::string fileName;
        int architecture;
        bool debug;
        bool printOutput;
        applyProgramArguments(fileType, fileName, architecture, debug, printOutput, argc, argv);

        ComputerArchitecture* piVersion = getArchitecture(architecture);
        Computer unit(*piVersion);

        Programmer programmer(fileType);
        programmer.program(fileName, unit);

        ControllerInterface interface(unit);
        std::thread t1([&interface, debug, printOutput](){interface.run(debug, printOutput);});

        run(unit, debug);
    }
    catch(std::invalid_argument& e)
    {
        std::cerr<<"Critical error: "+std::string(e.what())<<std::endl;
    }
}
