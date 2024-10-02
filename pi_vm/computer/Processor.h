//
// Created by player402 on 25.09.24.
//

#ifndef PI_VM_PROCESSOR_H
#define PI_VM_PROCESSOR_H

#include <cstdlib>
#include <stdexcept>
#include "Memory.h"
#include "../utils.h"

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
    T* registers;
    int registryCount;
    int registryAddressSpaceByteCount;
    Memory& memory;
    T instructionRegistry[2];
    int wordWidth;
    bool inProgrammingMode = false;

    bool lastOperationCarry;

    bool flags[3];

    enum LogicalOperation
    {
        ADD,
        MULTIPLY
    };

    void move(int destination, int source, bool reverse)
    {
        if(destination>=registryCount)
        {
            throw std::invalid_argument("Processor: [moving] First argument of the MOV instruction needs to be a registry number. Number of registers: "+std::to_string(registryCount)
            +". Address given: "+std::to_string(destination));
        }
        if(source<registryCount)    //Checking whether the source memory area is also a CPU register;
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
                memory.store(source-registryCount, registers[destination]);    //We are subtracting, because registers are co-addressed with memory and take up a few bits of address space.
            }
            else
            {
                registers[destination] = memory.load(source-registryCount);    //We are subtracting,  because registers are co-addressed with memory and take up a few bits of address space.
            }
        }
    }

    void flag(int flagNumber, bool value, bool negate, bool includeAccumulator, bool includeCarry, LogicalOperation operation)
    {
        bool accumulator = (bool)registers[ACCUMULATOR];
        if(includeAccumulator)
        {
            if(operation==ADD)
            {
                value = value | accumulator;
            }
            else if(operation==MULTIPLY)
            {
                value = value & accumulator;
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
            int result = registers[ALPHA] + registers[BETA];
            lastOperationCarry = (result>>wordWidth);
            registers[ACCUMULATOR] = result;
        }
    }

    void decodeAndExecute()
    {

        if((0b1000&instructionRegistry[0])==0)
        {
            if(flags[SKIP_FLAG])
            {
                return;
            }
            move(0b11&instructionRegistry[0], instructionRegistry[1], 0b100&instructionRegistry[0]);
        }
        else
        {
            if(flags[SKIP_FLAG] && ((0b110&instructionRegistry[0])>>1)!=SKIP_FLAG)
            {
                return;
            }
            flag((0b110&instructionRegistry[0])>>1, 0b1&instructionRegistry[0], 0b10&instructionRegistry[1], 0b100&instructionRegistry[1], 0b1000&instructionRegistry[1], 0b1&instructionRegistry[1] ? MULTIPLY : ADD);
        }
        triggerAccumulator();
    }

public:

    T getRegister(T registryNumber)
    {
        if(registryNumber<0 || registryNumber>=registryCount)
        {
            throw std::invalid_argument("Processor: [external registry read] Registry number given: "+std::to_string(registryNumber)+". Should be larger or equal 0 and below "+std::to_string(registryCount));
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
            instructionRegistry[0] = memory.load(registers[PROGRAM_COUNTER] - registryCount);
            instructionRegistry[1] = memory.load((registers[PROGRAM_COUNTER] + 1) - registryCount);
            registers[PROGRAM_COUNTER] += 2;
            decodeAndExecute();
        }
    }

    void setRegister(T registryNumber, T value)
    {
        if(registryNumber<0 || registryNumber>=registryCount)
        {
            throw std::invalid_argument("Processor: [external registry write] Registry number given: "+std::to_string(registryNumber)+". Should be larger or equal 0 and below "+std::to_string(registryCount));
        }
        registers[registryNumber] = value;
        if(registryNumber==ALPHA || registryNumber==BETA)
        {
            triggerAccumulator();
        }
    }

    void reset() {
        registers[PROGRAM_COUNTER] = registryCount;
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

    Processor(int registryAddressSpaceByteCount, Memory& memory, int wordWidth):memory(memory)
    {
        if(registryAddressSpaceByteCount<2)
        {
            throw std::invalid_argument("Processor: [initializing] Address space for CPU registers must be at least 2 bits wide - minimum 4 registers need to be created.");
        }
        registryCount = powerOfTwo(registryAddressSpaceByteCount);
        registers = (T*)malloc(registryCount*sizeof(T));
        this->wordWidth = wordWidth;
        this->registryAddressSpaceByteCount = registryAddressSpaceByteCount;
        reset();
    }

    ~Processor()
    {
        free(registers);
    }
};


#endif //PI_VM_PROCESSOR_H
