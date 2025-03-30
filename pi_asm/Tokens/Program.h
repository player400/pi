//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_PROGRAM_H
#define PI_ASM_PROGRAM_H


#include "Pattern.h"

class Program : public Pattern{
public:
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;
};


#endif //PI_ASM_PROGRAM_H
