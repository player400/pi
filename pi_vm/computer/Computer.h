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


public:

    int getRegistryCount() const
    {
        return architecture.getRegistryCount();
    }

    int getArchitectureWidth() const
    {
        return architecture.getWordWidth();
    }

    void cycle()
    {
        cpu->cycle();
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

    int output() const
    {
        return (int)cpu->getRegister(Processor<uint32_t>::ACCUMULATOR);
    }

    void input(int registryContent)
    {
        cpu->setRegister(Processor<uint32_t>::ACCUMULATOR, registryContent);
    }

    bool isStopped() const
    {
        return cpu->isStopped();
    };

    void program(uint32_t address, uint32_t value)
    {
        if(address<architecture.getRegistryCount())
        {
            cpu->setRegister(address, value);
        }
        else
        {
            ram->store(address-architecture.getRegistryCount(), value);
        }
    }

    Computer(ComputerArchitecture& piVersion):architecture(piVersion)
    {
        ram = new Memory(powerOfTwo(architecture.getMemoryAddressWidth()) - architecture.getRegistryCount());
        cpu = new Processor<uint32_t>(architecture, *ram);
    }

    ~Computer()
    {
        delete ram;
        delete cpu;
    }

};


#endif //PI_VM_COMPUTER_H
