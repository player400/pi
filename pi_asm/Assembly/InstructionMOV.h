//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_INSTRUCTIONMOV_H
#define PI_ASM_INSTRUCTIONMOV_H


#include "Assembly.h"
#include "AssemblyInstruction.h"

class InstructionMOV : public AssemblyInstruction{


    int source;
    int destination;
    bool reverse;
public:
    InstructionMOV(Writer &writer, Architecture architecture, int destination, bool reverse, int source);
    void write() override;
};


#endif //PI_ASM_INSTRUCTIONMOV_H
