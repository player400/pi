//
// Created by player402 on 07.04.25.
//

#ifndef PI_ASM_VARIABLE_H
#define PI_ASM_VARIABLE_H


#include "Pattern.h"
#include "Value.h"

class Variable : public Pattern{
Value* times= nullptr;
public:
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;

    ~Variable();
};


#endif //PI_ASM_VARIABLE_H
