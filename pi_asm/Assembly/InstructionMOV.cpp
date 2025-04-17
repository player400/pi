//
// Created by player402 on 17.04.25.
//

#include "InstructionMOV.h"

InstructionMOV::InstructionMOV(Writer &writer, Architecture architecture, int destination, bool reverse, int source)
        : AssemblyInstruction(writer, architecture),
          source(source),
          destination(destination),
          reverse(reverse){

}

void InstructionMOV::write() {
    uint8_t firstByte  = 0;
    uint8_t secondByte = 0;
    firstByte = firstByte << 1;
    firstByte += reverse;
    switch (architecture) {
        case Entity::BIT4: firstByte = firstByte << 2; break;
        case Entity::BIT8: firstByte = firstByte << 4; break;
    }
    firstByte+=destination;
    if(architecture == Entity::BIT8)
    {
        uint16_t address = source>>8;
        address = address & 0b11;
        firstByte = firstByte << 2;
        firstByte += address;
        secondByte = source & 0b11111111;
    }
    else if(architecture == Entity::BIT4)
    {
        secondByte = source;
    }
    writer.pushBack(firstByte);
    writer.pushBack(secondByte);
}
