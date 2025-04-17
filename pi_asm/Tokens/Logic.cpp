//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "Logic.h"
#include "Value.h"

unsigned int Logic::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset>=tokens.size())
    {
        return 0;
    }
    if(tokens[offset]==BOOLEAN_F)
    {
        type = BOOLEAN;
        value = false;
        return 1;
    }
    else if(tokens[offset]==BOOLEAN_T)
    {
        type = BOOLEAN;
        value = true;
        return 1;
    }
    else if(tokens[offset]==KW_CARRY)
    {
        type = CARRY;
        return 1;
    }
    else
    {
        Pattern* value = new Value;
        unsigned int valueMatch;
        try
        {
            valueMatch = value->match(tokens, offset);
        }
        catch(std::exception& e)
        {
            delete value;
            throw std::invalid_argument("[Parsing logical value] Syntax error: "+std::string(e.what()));
        }
        if(!valueMatch)
        {
            delete value;
            return 0;
        }
        else
        {
            patterns.push_back(value);
            type = ADDRESS;
            return valueMatch;
        }
    }
}

Logic::ValueType Logic::getType() const {
    return type;
}

const bool Logic::getValue() const {
    return value;
}
