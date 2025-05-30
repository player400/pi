//
// Created by player402 on 01.10.24.
//

#ifndef PI_VM_COMPUTER_H
#define PI_VM_COMPUTER_H


#include "Memory.h"
#include "Processor.h"
#include "architecture/Bit4.h"

class Computer {
private:
    Memory* ram;
    Processor<uint32_t>* cpu;
    ComputerArchitecture& architecture;
    long long unsigned int cycleCount = 0;

public:
    unsigned long long int getCycleCount() const {
        return cycleCount;
    }

    unsigned int getRegistryCount() const
    {
        return architecture.getRegistryCount();
    }

    unsigned int getArchitectureWidth() const
    {
        return architecture.getWordWidth();
    }

    unsigned int getRegister(int registryNumber) const
    {
        try
        {
            return (int)cpu->getRegister(registryNumber);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [reading register] Exception was thrown by the processor, while attempting to read the value of register "+std::to_string(registryNumber)+": "+std::string(e.what()));
        }
    }

    uint8_t getMemory(int address) const
    {
        try
        {
            return ram->load(address-architecture.getRegistryCount());
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [reading memory] Exception was thrown by the memory, while attempting to read the value at address "+std::to_string(address)+": "+std::string(e.what()));
        }
    }

    bool getFlag(int flagNumber) const
    {
        try
        {
            return cpu->getFlag(flagNumber);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [reading flag] Exception was thrown by the processor, while attempting to read the value of flag "+std::to_string(flagNumber)+": "+std::string(e.what()));
        }
    }
    void cycle()
    {
        try
        {
            if(cpu->cycle())
            {
                cycleCount++;
            }
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [clock cycle] The CPU threw an exception, when attempting a clock cycle: "+std::string(e.what()));
        }

    }

    void resume()
    {
        cpu->resume();
    }

    void programmingMode()
    {
        cpu->programmingMode();
    }

    void runningMode()
    {
        cpu->runningMode();
    }

    unsigned int output() const
    {
        try
        {
            return (int)cpu->getRegister(Processor<uint32_t>::ACCUMULATOR);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [reading output] Exception was thrown by the processor, while attempting to read the value of Accumulator: "+std::string(e.what()));
        }
    }

    void input(int registryContent)
    {
        try
        {
            cpu->setRegister(Processor<uint32_t>::ACCUMULATOR, registryContent);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [taking input] Exception was thrown by the CPU when setting the ACCUMULATOR: "+std::string(e.what()));
        }
    }

    bool isStopped() const
    {
        return cpu->isStopped();
    };

    void program(uint32_t address, uint32_t value)
    {
        if(address<architecture.getRegistryCount())
        {
            try
            {
                cpu->setRegister(address, value);
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("Computer: [programming register] Exception was thrown by the CPU when setting the value of "+std::to_string(address)+": "+std::string(e.what()));
            }
        }
        else
        {
            try
            {
                ram->store(address-architecture.getRegistryCount(), value);
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("Computer: [programming memory] Exception was thrown by the CPU when setting the value of "+std::to_string(address)+" memory address: "+std::string(e.what()));
            }
        }
    }

    Computer(ComputerArchitecture& piVersion):architecture(piVersion)
    {
        try
        {
            ram = new Memory(powerOfTwo(architecture.getMemoryAddressWidth()) - architecture.getRegistryCount());
            cpu = new Processor<uint32_t>(architecture, *ram);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Computer: [initializing] Exception was thrown by either the Processor or the memory constructor: "+std::string(e.what()));
        }
    }

    ~Computer()
    {
        delete ram;
        delete cpu;
    }

};


#endif //PI_VM_COMPUTER_H
