//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_LOGIC_H
#define PI_ASM_LOGIC_H


#include "Pattern.h"

class Logic : public Pattern{
    enum ValueType
    {
        ADDRESS,
        BOOLEAN,
        CARRY
    };
    ValueType type;
    std::string value;
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;
};


#endif //PI_ASM_LOGIC_H
