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
    ComputerArchitecture* architecture;


public:

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

    int output()
    {
        return (int)cpu->getAccumulator();
    }

    void input(int registryContent)
    {
        cpu->setRegister(Processor<uint32_t>::ACCUMULATOR, registryContent);
    }

    bool isStopped()
    {
        return cpu->isStopped();
    };

    void program(uint32_t address, uint32_t value)
    {
        if(address<4)
        {
            cpu->setRegister(address, value);
        }
        else
        {
            ram->store(address-4, value&0xFF);
        }
    }

    Computer()
    {
        architecture = new Bit4;
        ram = new Memory(12);
        cpu = new Processor<uint32_t>(architecture, ram);
    }

    ~Computer()
    {
        delete architecture;
    }

};


#endif //PI_VM_COMPUTER_H
