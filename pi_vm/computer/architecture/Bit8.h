//
// Created by player402 on 21.03.25.
//

#ifndef PI_VM_BIT8_H
#define PI_VM_BIT8_H


#include <cstdint>
#include "ComputerArchitecture.h"
#include "../../utils.h"

class Bit8 : public ComputerArchitecture {

private:
    const int wordWidth = 8;
    const int registryAddressSpaceByteCount = 4;

    int registryCount;

    const int opCodeBitmask = 0b1000000000000000;
    const int opCodeShift = 15;


    //CONSTANT VARIABLES BELOW
    //Allow for extraction of arguments from instruction codes
    //For example flag number in the FLAG instruction is on the 6th and 7th bit, so the bitmask is 1100000 and after applying it you need to bitshift by 5.
    //Naming pattern of those variables: <instruction (mov or flag)><argument (destination, source, flag number etc)><Bitmask/Shift>

    //MOV OPERATION INSTRUCTION CODE SPECIFICS:

    const int movOpCode = 0;

    const int movReverseBitmask = 0b100000000000000;    //& WITH THIS
    const int movReverseShift = 14;  //THEN BITSHIFT LEFT THIS

    const int movDestinationBitmask = 0b11110000000000;
    const int movDestinationShift = 10;

    const int movSourceBitmask = 0b1111111111;
    const int movSourceShift = 0;


    //FLAG OPERATION INSTRUCTION CODE SPECIFICS

    const int flagFlagNumberBitmask = 0b0110000000000000;
    const int flagFlagNumberShift = 13;

    const int flagValueBitmask = 0b1000000000000;
    const int flagValueShift = 12;

    const int flagCarryBitmask = 0b100000000000;
    const int flagCarryShift = 11;

    const int flagMemoryBitmask = 0b10000000000;
    const int flagMemoryShift = 10;

    const int flagNegationBitmask = 0b100000000;
    const int flagNegationShift = 8;

    const int flagLogicalOperationBitmask = 0b1000000000;
    const int flagLogicalOperationShift = 9;

    const int flagMultiplyLogicalOperationCode = 1;

    const int flagAddressBitmask = 0b11111111;
    const int flagAddressShift = 0;

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
        return 10;
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
        return (bool)((flagMemoryBitmask & instruction) >> flagMemoryShift);
    }

    int getFlagSourceRegisterNumber(uint64_t instruction) override
    {
        return (int)((flagMemoryBitmask & instruction) >> flagMemoryShift);
    }

    int getMemoryCellWidth() override
    {
        return 8;
    }

    LogicalOperation getFlagLogicalOperation(uint64_t instruction) override
    {
        return ((instruction & flagLogicalOperationBitmask) >> flagLogicalOperationShift) == flagMultiplyLogicalOperationCode ? MULTIPLY : ADD;
    }



    Bit8()
    {
        registryCount = powerOfTwo(registryAddressSpaceByteCount);
    }
};


#endif //PI_VM_BIT8_H
