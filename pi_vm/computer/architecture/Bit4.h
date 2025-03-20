//
// Created by player402 on 02.10.24.
//

#ifndef PI_VM_BIT4_H
#define PI_VM_BIT4_H


#include "ComputerArchitecture.h"
#include "../../utils.h"

class Bit4 : public ComputerArchitecture{
private:
    const int wordWidth = 4;
    const int registryAddressSpaceByteCount = 2;

    int registryCount;

    const int opCodeBitmask = 0b10000000;
    const int opCodeShift = 7;


    //CONSTANT VARIABLES BELOW
    //Allow for extraction of arguments from instruction codes
    //For example flag number in the FLAG instruction is on the 6th and 7th bit, so the bitmask is 1100000 and after applying it you need to bitshift by 5.
    //Naming pattern of those variables: <instruction (mov or flag)><argument (destination, source, flag number etc)><Bitmask/Shift>

    //MOV OPERATION INSTRUCTION CODE SPECIFICS:

    const int movOpCode = 0;

    const int movReverseBitmask = 0b1000000;    //& WITH THIS
    const int movReverseShift = 6;  //THEN BITSHIFT LEFT THIS

    const int movDestinationBitmask = 0b110000;
    const int movDestinationShift = 4;

    const int movSourceBitmask = 0b1111;
    const int movSourceShift = 0;


    //FLAG OPERATION INSTRUCTION CODE SPECIFICS

    const int defaultFlagSourceRegistry = 3;    //In 4-bit PI assembly there is no argument in the FLAG instruction to specify source register - it's always the accumulator

    const int flagFlagNumberBitmask = 0b01100000;
    const int flagFlagNumberShift = 5;

    const int flagValueBitmask = 0b10000;
    const int flagValueShift = 4;

    const int flagCarryBitmask = 0b1000;
    const int flagCarryShift = 3;

    const int flagAccumulatorBitmask = 0b100;
    const int flagAccumulatorShift = 2;

    const int flagNegationBitmask = 0b10;
    const int flagNegationShift = 1;

    const int flagLogicalOperationBitmask = 0b1;
    const int flagLogicalOperationShift = 0;

    const int flagMultiplyLogicalOperationCode = 1;



public:
    int getRegistryCount() override
    {
        return registryCount;
    }

    int getWordWidth() override
    {
        return wordWidth;
    }

    int getMemoryAddressWidth() override
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

    int getMovDestination(uint64_t instruction) override
    {
        return (int)((movDestinationBitmask & instruction)>>movDestinationShift);
    }

    int getMovSource(uint64_t instruction) override
    {
        return (int)((movSourceBitmask & instruction)>>movSourceShift);
    }

    int getFlagFlagNumber(uint64_t instruction) override
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

    int getFlagSourceRegisterNumber(uint64_t instruction) override
    {
        return defaultFlagSourceRegistry;
    }

    int getMemoryCellWidth() override
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
