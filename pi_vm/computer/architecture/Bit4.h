//
// Created by player402 on 02.10.24.
//

#ifndef PI_VM_BIT4_H
#define PI_VM_BIT4_H


#include "ComputerArchitecture.h"
#include "../../utils.h"

class Bit4 : public ComputerArchitecture{
private:
    const unsigned int wordWidth = 4;
    const unsigned int registryAddressSpaceByteCount = 2;

    unsigned int registryCount;

    const unsigned int opCodeBitmask = 0b10000000;
    const unsigned int opCodeShift = 7;


    //CONSTANT VARIABLES BELOW
    //Allow for extraction of arguments from instruction codes
    //For example flag number in the FLAG instruction is on the 6th and 7th bit, so the bitmask is 1100000 and after applying it you need to bitshift by 5.
    //Naming pattern of those variables: <instruction (mov or flag)><argument (destination, source, flag number etc)><Bitmask/Shift>

    //MOV OPERATION INSTRUCTION CODE SPECIFICS:

    const unsigned int movOpCode = 0;

    const unsigned int movReverseBitmask = 0b1000000;    //& WITH THIS
    const unsigned int movReverseShift = 6;  //THEN BITSHIFT LEFT THIS

    const unsigned int movDestinationBitmask = 0b110000;
    const unsigned int movDestinationShift = 4;

    const unsigned int movSourceBitmask = 0b1111;
    const unsigned int movSourceShift = 0;


    //FLAG OPERATION INSTRUCTION CODE SPECIFICS

    const unsigned int defaultFlagSourceRegistry = 3;    //In 4-bit PI assembly there is no argument in the FLAG instruction to specify source register - it's always the accumulator

    const unsigned int flagFlagNumberBitmask = 0b01100000;
    const unsigned int flagFlagNumberShift = 5;

    const unsigned int flagValueBitmask = 0b10000;
    const unsigned int flagValueShift = 4;

    const unsigned int flagCarryBitmask = 0b1000;
    const unsigned int flagCarryShift = 3;

    const unsigned int flagAccumulatorBitmask = 0b100;
    const unsigned int flagAccumulatorShift = 2;

    const unsigned int flagNegationBitmask = 0b10;
    const unsigned int flagNegationShift = 1;

    const unsigned int flagLogicalOperationBitmask = 0b1;
    const unsigned int flagLogicalOperationShift = 0;

    const unsigned int flagMultiplyLogicalOperationCode = 1;



public:
    unsigned int getRegistryCount() override
    {
        return registryCount;
    }

    int unsigned getWordWidth() override
    {
        return wordWidth;
    }

    int unsigned getMemoryAddressWidth() override
    {
        return getWordWidth();
    }

    bool isMoveOperation(uint64_t instruction) override
    {
        if(((instruction & opCodeBitmask)>>opCodeShift) == movOpCode)
        {
            return true;
        }
        return false;
    }

    bool isMoveDirectionReversed(uint64_t instruction) override
    {
        return ((movReverseBitmask & instruction)>>movReverseShift);
    }

    int unsigned getMovDestination(uint64_t instruction) override
    {
        return (int)((movDestinationBitmask & instruction)>>movDestinationShift);
    }

    int unsigned getMovSource(uint64_t instruction) override
    {
        return (int)((movSourceBitmask & instruction)>>movSourceShift);
    }

    int unsigned getFlagFlagNumber(uint64_t instruction) override
    {
        return (int)((flagFlagNumberBitmask & instruction)>>flagFlagNumberShift);
    }

    bool getFlagValue(uint64_t instruction) override
    {
        return (bool)((flagValueBitmask & instruction)>>flagValueShift);
    }

    bool isFlagNegated(uint64_t instruction) override
    {
        return (bool)((flagNegationBitmask & instruction)>>flagNegationShift);
    }

    bool isFlagCarryIncluded(uint64_t instruction) override
    {
        return (bool)((flagCarryBitmask & instruction)>>flagCarryShift);
    }

    bool isFlagRegisterIncluded(uint64_t instruction) override
    {
        return (bool)((flagAccumulatorBitmask & instruction)>>flagAccumulatorShift);
    }

    int unsigned getFlagSourceRegisterNumber(uint64_t) override
    {
        return defaultFlagSourceRegistry;
    }

    int unsigned getMemoryCellWidth() override
    {
        return 4;
    }

    LogicalOperation getFlagLogicalOperation(uint64_t instruction) override
    {
        return ((instruction & flagLogicalOperationBitmask) >> flagLogicalOperationShift) == flagMultiplyLogicalOperationCode ? MULTIPLY : ADD;
    }

    Bit4()
    {
        registryCount = powerOfTwo(registryAddressSpaceByteCount);
    }
};


#endif //PI_VM_BIT4_H
