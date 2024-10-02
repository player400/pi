//
// Created by player402 on 01.10.24.
//

#ifndef PI_VM_COMPUTER_H
#define PI_VM_COMPUTER_H


#include "Memory.h"
#include "Processor.h"

class Computer {
private:
    Memory ram;
    Processor<uint32_t> cpu;



public:

    void cycle()
    {
        cpu.cycle();
    }

    void resume()
    {
        cpu.resume();
    }

    void programmingMode()
    {
        cpu.programmingMode();
    }

    void runningMode()
    {
        cpu.runningMode();
    }

    int output()
    {
        return (int)cpu.getAccumulator();
    }

    void input(int registryContent)
    {
        cpu.setRegister(Processor<uint32_t>::ACCUMULATOR, registryContent);
    }

    bool isStopped()
    {
        return cpu.isStopped();
    };

    void program(uint32_t address, uint32_t value)
    {
        if(address<4)
        {
            cpu.setRegister(address, value);
        }
        else
        {
            ram.store(address-4, value&0xFF);
        }
    }

    Computer():ram(12),cpu(2, ram, 4)
    {

    }

};


#endif //PI_VM_COMPUTER_H
