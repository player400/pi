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

#define FLAG_COUNT 4

//This class is an abstraction of computer CPU - template should be uint8, uint16, uint32 etc - depending on how many bit system you want to have
template<typename T>
class Processor {
public:
    static const int PROGRAM_COUNTER = 0;
    static const int ALPHA = 1;
    static const int BETA = 2;
    static const int ACCUMULATOR = 3;

    static const int ALU_FLAG_2 = 3;
    static const int ALU_FLAG_1 = 2;
    static const int HALT_FLAG = 0;
    static const int SKIP_FLAG = 1;

private:
    ComputerArchitecture& architecture;

    T* registers;
    Memory& memory;
    uint64_t instructionRegistry;
    bool inProgrammingMode = false;

    bool lastOperationCarry = false;

    bool flags[FLAG_COUNT];

    void triggerAccumulator()
    {
        try
        {
            if(flags[ALU_FLAG_1])
            {
                if(flags[ALU_FLAG_2])
                {
                    setRegister(ACCUMULATOR,  ~(getRegister(ALPHA) | getRegister(BETA)));
                }
                else
                {
                    setRegister(ACCUMULATOR,  ~(getRegister(ALPHA) & getRegister(BETA)));
                }
            }
            else
            {
                uint64_t result;
                if(flags[ALU_FLAG_2])
                {
                    result = getRegister(ALPHA) - getRegister(BETA);
                }
                else
                {
                    result = getRegister(ALPHA) + getRegister(BETA);
                }
                lastOperationCarry = ((result>>architecture.getWordWidth())&0b1);
                setRegister(ACCUMULATOR, result);
            }
        }
        catch (std::exception &e) {
            throw std::invalid_argument(
                    "Processor: [alu calculations] Exception was thrown, while attempting to compute the new value of ALU: " +
                    std::string(e.what()));
        }
    }


public:
    bool getFlag(int flagNumber) const
    {
        if(flagNumber < 0 || flagNumber>=FLAG_COUNT)
        {
            throw std::invalid_argument("Processor: [flag read] Flag number given: "+std::to_string(flagNumber)
                                        +". Should be larger or equal 0 and below "+std::to_string(FLAG_COUNT));
        }
        return flags[flagNumber];
    }

    T getRegister(T registryNumber) const
    {
        if(registryNumber<0 || registryNumber>=architecture.getRegistryCount())
        {
            throw std::invalid_argument("Processor: [registry read] Registry number given: "+std::to_string(registryNumber)
                                        +". Should be larger or equal 0 and below "+std::to_string(architecture.getRegistryCount()));
        }
        return registers[registryNumber];
    }

    void setRegister(T registryNumber, T value)
    {
        uint64_t bitmask = 0;
        uint64_t bitmaskConstructor=1;
        for(unsigned int i=0;i<architecture.getWordWidth();i++)
        {
            bitmask = bitmask | bitmaskConstructor;
            bitmaskConstructor = bitmaskConstructor<<1;
        }
        if(registryNumber<0 || registryNumber>=architecture.getRegistryCount())
        {
            throw std::invalid_argument("Processor: [registry write] Registry number given: "+std::to_string(registryNumber)
                                        +". Should be larger or equal 0 and below "+std::to_string(architecture.getRegistryCount()));
        }
        if(registryNumber==PROGRAM_COUNTER && value%2==1)
        {
            value--;
        }
        registers[registryNumber] = bitmask&value;
        if(registryNumber==ALPHA || registryNumber==BETA)
        {
            triggerAccumulator();
        }
    }

private:
    void mov(unsigned int destination, unsigned int source, bool reverse)
    {
        if(destination>=architecture.getRegistryCount())
        {
            throw std::invalid_argument("Processor: [moving] First argument of the MOV instruction needs to be a registry number. Number of registers: "+std::to_string(architecture.getRegistryCount())
            +". Address given: "+std::to_string(destination));
        }
        try
        {
            if(source<architecture.getRegistryCount())    //Checking whether the source memory area is also a CPU register;
            {
                if(reverse)
                {
                    setRegister(source, getRegister(destination));
                }
                else
                {
                    setRegister(destination, getRegister(source));
                }
            }
            else
            {
                if(reverse)
                {
                    memory.store(source-architecture.getRegistryCount(), getRegister(destination));    //We are subtracting, because registers are co-addressed with memory and take up a few bits of address space.
                }
                else
                {
                    setRegister(destination, memory.load(source-architecture.getRegistryCount()));    //We are subtracting, because registers are co-addressed with memory and take up a few bits of address space.
                }
            }
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Processor: [moving] Exception was thrown, while executing the MOV instruction. Current value of Program Counter (post-incrementation) is "+std::to_string(registers[PROGRAM_COUNTER])+": "+std::string(e.what()));
        }
    }

    void flag(unsigned int flagNumber, bool value, bool negate, bool includeMemory, bool includeCarry, unsigned int sourceMemoryAddress, LogicalOperation operation)
    {
        if(includeMemory)
        {
            bool sourceRegistry;
            try
            {
                sourceRegistry = sourceMemoryAddress < architecture.getRegistryCount() ? (bool) getRegister(sourceMemoryAddress) : memory.load(sourceMemoryAddress-architecture.getRegistryCount());
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("Processor: [flag] Exception was thrown, while fetching value of register or memory to execute the FLAG instruction. Current value of Program Counter (post-incrementation) is "+std::to_string(registers[PROGRAM_COUNTER])+": "+std::string(e.what()));
            }
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


    void decodeAndExecute()
    {

        if(architecture.isMoveOperation(instructionRegistry))
        {
            if(flags[SKIP_FLAG])
            {
                return;
            }
            mov(architecture.getMovDestination(instructionRegistry),
                 architecture.getMovSource(instructionRegistry),
                 architecture.isMoveDirectionReversed(instructionRegistry));
        }
        else
        {
            if(flags[SKIP_FLAG] && (architecture.getFlagFlagNumber(instructionRegistry))!=SKIP_FLAG)   //If skip flag is set all instructions are skipped, except FLAG instruction changing the skip flag
            {
                return;
            }
            flag(architecture.getFlagFlagNumber(instructionRegistry),
                 architecture.getFlagValue(instructionRegistry),
                 architecture.isFlagNegated(instructionRegistry),
                 architecture.isFlagRegisterIncluded(instructionRegistry),
                 architecture.isFlagCarryIncluded(instructionRegistry),
                 architecture.getFlagSourceRegisterNumber(instructionRegistry),
                 architecture.getFlagLogicalOperation(instructionRegistry));
        }
    }

public:
    bool cycle()
    {
        if(!inProgrammingMode) {
            if (flags[HALT_FLAG]) {
                return false;
            }
            try {
                if (registers[PROGRAM_COUNTER] < architecture.getRegistryCount()) {
                    try {
                        instructionRegistry = getRegister(getRegister(PROGRAM_COUNTER));
                        instructionRegistry = instructionRegistry << architecture.getWordWidth();
                        instructionRegistry += getRegister(getRegister(PROGRAM_COUNTER) + 1);
                    }
                    catch (std::exception &e) {
                        throw std::invalid_argument(
                                "Processor: [reading instruction from registers] Exception was thrown, while attempting to read the value of a register: " +
                                std::string(e.what()));
                    }
                } else {
                    try {
                        instructionRegistry = memory.load(
                                getRegister(PROGRAM_COUNTER) - architecture.getRegistryCount());
                        for (unsigned int i = 1;
                             i < 2 * (architecture.getWordWidth() / architecture.getMemoryCellWidth()); i++) {
                            instructionRegistry = instructionRegistry << architecture.getWordWidth();
                            instructionRegistry += memory.load(
                                    (getRegister(PROGRAM_COUNTER) + i) - architecture.getRegistryCount());

                        }
                    }
                    catch (std::exception &e) {
                        throw std::invalid_argument(
                                "Processor: [reading instruction from memory] Exception was thrown, while attempting to read registers or memory: " +
                                std::string(e.what()));
                    }
                }
            }
            catch (std::exception &e) {
                throw std::invalid_argument(
                        "Processor: [reading program counter] Exception was thrown, while attempting to read the value of Program Counter (register 0): " +
                        std::string(e.what()));
            }
            try
            {
                setRegister(PROGRAM_COUNTER, getRegister(PROGRAM_COUNTER)+2);
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument(
                        "Processor: [incrementing program counter] Exception was thrown, while attempting to increment the value of Program Counter (register 0): " +
                        std::string(e.what()));
            }
            decodeAndExecute();
            return true;
        }
        return false;
    }

    void reset() {
        flags[HALT_FLAG] = false;
        flags[SKIP_FLAG] = false;
        flags[ALU_FLAG_1] = false;
        flags[ALU_FLAG_2] = false;
    }

    bool isStopped() const
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

    Processor(ComputerArchitecture& architecture, Memory& memory):architecture(architecture), memory(memory)
    {
        registers = (T*)malloc(architecture.getRegistryCount()*sizeof(T));
        reset();
    }

    ~Processor()
    {
        free(registers);
    }


};


#endif //PI_VM_PROCESSOR_H
