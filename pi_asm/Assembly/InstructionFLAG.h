//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_INSTRUCTIONFLAG_H
#define PI_ASM_INSTRUCTIONFLAG_H


#include "AssemblyInstruction.h"

class InstructionFLAG : public AssemblyInstruction{
public:
    enum Operation
    {
        MULTIPLY,
        ADD
    };
private:

    int flag;
    int address;
    bool value;
    bool carry;
    bool memory;
    bool negate;
    Operation operation;
public:
    void write() override;

    InstructionFLAG(Writer &writer, Architecture architecture, int flag, bool value, bool carry, bool memory,
                    int address, bool negate, InstructionFLAG::Operation operation);

};


#endif //PI_ASM_INSTRUCTIONFLAG_H
