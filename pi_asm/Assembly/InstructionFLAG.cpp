//
// Created by player402 on 17.04.25.
//

#include "InstructionFLAG.h"

void InstructionFLAG::write() {
    uint8_t first_byte = 1;
    first_byte = first_byte << 2;
    first_byte += flag;
    first_byte = first_byte << 1;
    first_byte += value ? 1 : 0;
    uint8_t second_byte;
    if(architecture == BIT8)
    {
        first_byte = first_byte << 1;
        first_byte += carry ? 1 : 0;
        first_byte = first_byte << 1;
        first_byte += memory ? 1 : 0;
        first_byte = first_byte << 1;
        first_byte += operation == MULTIPLY ? 1 : 0;
        first_byte = first_byte << 1;
        first_byte += negate ? 1 : 0;
        second_byte = address;
    }
    else
    {
        second_byte = carry ? 1 : 0;
        second_byte = second_byte << 1;
        second_byte += memory ? 1 : 0;
        second_byte = second_byte << 1;
        second_byte += negate ? 1 : 0;
        second_byte = second_byte << 1;
        second_byte += operation == MULTIPLY ? 1 : 0;
    }
    writer.pushBack(first_byte);
    writer.pushBack(second_byte);
}

InstructionFLAG::InstructionFLAG(Writer &writer, Architecture architecture, int flag, bool value, bool carry,
                                 bool memory,
                                 int address, bool negate, InstructionFLAG::Operation operation) : AssemblyInstruction(writer, architecture),
                                                                                      flag(flag), address(address),
                                                                                      value(value), carry(carry),
                                                                                      memory(memory), negate(negate),
                                                                                      operation(operation)
{

}

