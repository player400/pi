//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_ASSEMBLYINSTRUCTION_H
#define PI_ASM_ASSEMBLYINSTRUCTION_H


#include "Entity.h"

class AssemblyInstruction : public Entity
{

protected:
    explicit AssemblyInstruction(Writer &writer, Architecture architecture);
};


#endif //PI_ASM_ASSEMBLYINSTRUCTION_H
