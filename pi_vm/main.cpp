
#include "computer/Computer.h"
#include "ControllerInterface.h"
#include "ProgramArgumentProcessing.h"
#include "programmer/Programmer.h"
#include "computer/architecture/Bit8.h"
#include <thread>



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


int main(int argc, char* argv[]) {

    try
    {
        ExecutableFileType fileType;
        std::string fileName;
        int architecture;
        applyProgramArguments(fileType, fileName, architecture, argc, argv);

        ComputerArchitecture* piVersion = getArchitecture(architecture);
        Computer unit(*piVersion);

        Programmer programmer(fileType);
        programmer.program(fileName, unit);

        ControllerInterface interface(unit);
        std::thread t1([&interface](){interface.run();});

        while(true)
        {
            unit.cycle();
        }
    }
    catch(std::invalid_argument& e)
    {
        std::cerr<<"Critical error: "+std::string(e.what())<<std::endl;
    }
}
