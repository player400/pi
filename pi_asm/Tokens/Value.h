//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_VALUE_H
#define PI_ASM_VALUE_H


#include "Pattern.h"

class Value : public Pattern {
public:
    enum Type
    {
        DIRECT,
        DECLARATION,
        REFERENCE
    };
private:
    std::string value;
    Type type;
public:
    const std::string &getValue() const;

    Type getType() const;

    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;
};


#endif //PI_ASM_VALUE_H
