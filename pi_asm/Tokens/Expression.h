//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_EXPRESSION_H
#define PI_ASM_EXPRESSION_H


#include "Pattern.h"

class Expression : public Pattern{
public:
    enum OperationType
    {
        ADD,
        MUL
    };
private:
    bool negate =  false;

    OperationType type;

    unsigned int matchAddOns(std::vector<std::string> &tokens, unsigned int offset);
public:
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;

    bool isNegate() const;

    OperationType getType() const;
};


#endif //PI_ASM_EXPRESSION_H
