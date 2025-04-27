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
    const unsigned int wordWidth = 8;
    const unsigned int registryAddressSpaceByteCount = 4;

    unsigned int registryCount;

    const unsigned int opCodeBitmask = 0b1000000000000000;
    const unsigned int opCodeShift = 15;


    //CONSTANT VARIABLES BELOW
    //Allow for extraction of arguments from instruction codes
    //For example flag number in the FLAG instruction is on the 6th and 7th bit, so the bitmask is 1100000 and after applying it you need to bitshift by 5.
    //Naming pattern of those variables: <instruction (mov or flag)><argument (destination, source, flag number etc)><Bitmask/Shift>

    //MOV OPERATION INSTRUCTION CODE SPECIFICS:

    const unsigned int movOpCode = 0;

    const unsigned int movReverseBitmask = 0b100000000000000;    //& WITH THIS
    const unsigned int movReverseShift = 14;  //THEN BITSHIFT LEFT THIS

    const unsigned int movDestinationBitmask = 0b11110000000000;
    const unsigned int movDestinationShift = 10;

    const unsigned int movSourceBitmask = 0b1111111111;
    const unsigned int movSourceShift = 0;


    //FLAG OPERATION INSTRUCTION CODE SPECIFICS

    const unsigned int flagFlagNumberBitmask = 0b0110000000000000;
    const unsigned int flagFlagNumberShift = 13;

    const unsigned int flagValueBitmask = 0b1000000000000;
    const unsigned int flagValueShift = 12;

    const unsigned int flagCarryBitmask = 0b100000000000;
    const unsigned int flagCarryShift = 11;

    const unsigned int flagMemoryBitmask = 0b10000000000;
    const unsigned int flagMemoryShift = 10;

    const unsigned int flagNegationBitmask = 0b100000000;
    const unsigned int flagNegationShift = 8;

    const unsigned int flagLogicalOperationBitmask = 0b1000000000;
    const unsigned int flagLogicalOperationShift = 9;

    const unsigned int flagMultiplyLogicalOperationCode = 1;

    const unsigned int flagAddressBitmask = 0b11111111;
    const unsigned int flagAddressShift = 0;

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
        return (bool)((flagMemoryBitmask & instruction) >> flagMemoryShift);
    }

    int unsigned getFlagSourceRegisterNumber(uint64_t instruction) override
    {
        return (int)((flagAddressBitmask & instruction) >> flagAddressShift);
    }

    int unsigned getMemoryCellWidth() override
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
