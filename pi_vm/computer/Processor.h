//
// Created by player402 on 25.09.24.
//

#ifndef PI_VM_PROCESSOR_H
#define PI_VM_PROCESSOR_H

#include <cstdlib>
#include <stdexcept>
#include "Memory.h"
#include "../utils.h"
#include "architecture/ComputerArchitecture.h"

//This class is an abstraction of computer CPU - template should be uint8, uint16, uint32 etc - depending on how many bit system you want to have
template<typename T>
class Processor {
public:
    static const int PROGRAM_COUNTER = 0;
    static const int ALPHA = 1;
    static const int BETA = 2;
    static const int ACCUMULATOR = 3;

    static const int ALU_FLAG = 2;
    static const int HALT_FLAG = 0;
    static const int SKIP_FLAG = 1;

private:
    ComputerArchitecture* architecture;

    T* registers;
    Memory* memory;
    uint64_t instructionRegistry;
    bool inProgrammingMode = false;

    bool lastOperationCarry;

    bool flags[3];

    void mov(int destination, int source, bool reverse)
    {
        if(destination>=architecture->getRegistryCount())
        {
            throw std::invalid_argument("Processor: [moving] First argument of the MOV instruction needs to be a registry number. Number of registers: "+std::to_string(architecture->getRegistryCount())
            +". Address given: "+std::to_string(destination));
        }
        if(source<architecture->getRegistryCount())    //Checking whether the source memory area is also a CPU register;
        {
            if(reverse)
            {
                registers[source] = registers[destination];
            }
            else
            {
                registers[destination] = registers[source];
            }
        }
        else
        {
            if(reverse)
            {
                memory->store(source-architecture->getRegistryCount(), registers[destination]);    //We are subtracting, because registers are co-addressed with memory and take up a few bits of address space.
            }
            else
            {
                registers[destination] = memory->load(source-architecture->getRegistryCount());    //We are subtracting, because registers are co-addressed with memory and take up a few bits of address space.
            }
        }
    }

    void flag(int flagNumber, bool value, bool negate, bool includeRegister, bool includeCarry, int sourceRegistryNumber, LogicalOperation operation)
    {
        bool sourceRegistry = (bool)registers[sourceRegistryNumber];
        if(includeRegister)
        {
            if(operation==ADD)
            {
                value = value | sourceRegistry;
            }
            else if(operation==MULTIPLY)
            {
                value = value & sourceRegistry;
            }
        }
        if(includeCarry)
        {
            if(operation==ADD)
            {
                value = value | lastOperationCarry;
            }
            else if(operation==MULTIPLY)
            {
                value = value & lastOperationCarry;
            }
        }
        if(negate)
        {
            value = !value;
        }
        flags[flagNumber] = value;
    }

    void triggerAccumulator()
    {
        if(flags[ALU_FLAG])
        {
            registers[ACCUMULATOR] = ~(registers[ALPHA] & registers[BETA]);
        }
        else
        {
            uint64_t result = registers[ALPHA] + registers[BETA];
            lastOperationCarry = (result>>architecture->getWordWidth());
            registers[ACCUMULATOR] = result;
        }
    }

    void decodeAndExecute()
    {

        if(architecture->isMoveOperation(instructionRegistry))
        {
            if(flags[SKIP_FLAG])
            {
                return;
            }
            mov(architecture->getMovDestination(instructionRegistry),
                 architecture->getMovSource(instructionRegistry),
                 architecture->isMoveDirectionReversed(instructionRegistry));
        }
        else
        {
            if(flags[SKIP_FLAG] && (architecture->getFlagFlagNumber(instructionRegistry))!=SKIP_FLAG)   //If skip flag is set all instructions are skipped, except FLAG instruction changing the skip flag
            {
                return;
            }
            flag(architecture->getFlagFlagNumber(instructionRegistry),
                 architecture->getFlagValue(instructionRegistry),
                 architecture->isFlagNegated(instructionRegistry),
                 architecture->isFlagRegisterIncluded(instructionRegistry),
                 architecture->isFlagCarryIncluded(instructionRegistry),
                 architecture->getFlagSourceRegisterNumber(instructionRegistry),
                 architecture->getFlagLogicalOperation(instructionRegistry));
        }
        triggerAccumulator();
    }

public:

    T getRegister(T registryNumber)
    {
        if(registryNumber<0 || registryNumber>=architecture->getRegistryCount())
        {
            throw std::invalid_argument("Processor: [external registry read] Registry number given: "+std::to_string(registryNumber)
            +". Should be larger or equal 0 and below "+std::to_string(architecture->getRegistryCount()));
        }
        return registers[registryNumber];
    }

    T getAccumulator()
    {
        triggerAccumulator();
        return getRegister(ACCUMULATOR);
    }

    void cycle()
    {
        if(!inProgrammingMode) {
            if (flags[HALT_FLAG]) {
                return;
            }
            instructionRegistry = memory->load(registers[PROGRAM_COUNTER] - architecture->getRegistryCount());
            instructionRegistry = instructionRegistry << architecture->getWordWidth();
            instructionRegistry += memory->load((registers[PROGRAM_COUNTER] + 1) - architecture->getRegistryCount());
            registers[PROGRAM_COUNTER] += 2;
            decodeAndExecute();
        }
    }

    void setRegister(T registryNumber, T value)
    {
        if(registryNumber<0 || registryNumber>=architecture->getRegistryCount())
        {
            throw std::invalid_argument("Processor: [external registry write] Registry number given: "+std::to_string(registryNumber)
            +". Should be larger or equal 0 and below "+std::to_string(architecture->getRegistryCount()));
        }
        registers[registryNumber] = value;
        if(registryNumber==ALPHA || registryNumber==BETA)
        {
            triggerAccumulator();
        }
    }

    void reset() {
        registers[PROGRAM_COUNTER] = architecture->getRegistryCount();
        triggerAccumulator();
    }

    bool isStopped()
    {
        return flags[HALT_FLAG];
    }

    void resume()
    {
        flags[HALT_FLAG] = false;
    }

    void programmingMode()
    {
        inProgrammingMode = true;
    }

    void runningMode()
    {
        inProgrammingMode = false;
    }

    Processor(ComputerArchitecture* architecture, Memory* memory):memory(memory)
    {
        this->architecture = architecture;
        registers = (T*)malloc(architecture->getRegistryCount()*sizeof(T));
        reset();
    }

    ~Processor()
    {
        free(registers);
    }
};


#endif //PI_VM_PROCESSOR_H
