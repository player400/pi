//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_ASSEMBLYINSTRUCTION_H
#define PI_ASM_INSTRUCTION_H


#include "Pattern.h"

class Instruction : public Pattern{
public:
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;
};


#endif //PI_ASM_ASSEMBLYINSTRUCTION_H
