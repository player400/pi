//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_LOGIC_H
#define PI_ASM_LOGIC_H


#include "Pattern.h"

class Logic : public Pattern{
public:
    enum ValueType
    {
        ADDRESS,
        BOOLEAN,
        CARRY
    };
private:
    ValueType type;
    bool value;
public:
    ValueType getType() const;

    const bool getValue() const;

    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;


};


#endif //PI_ASM_LOGIC_H
