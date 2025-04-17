//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include <algorithm>
#include "Value.h"

unsigned int Value::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset>=tokens.size())
    {
        return 0;
    }
    type = DECLARATION;
    for(int i=0;i<std::string(VALUE_DECLARATION).size();i++)
    {
        if(tokens[offset][i] != VALUE_DECLARATION[i])
        {
            type = DIRECT;
            break;
        }
    }
    if(type == DECLARATION)
    {
        if(std::string(VALUE_DECLARATION).size()>= tokens[offset].size())
        {
            throw std::invalid_argument("[Parsing value] Expected a declaration name after "+std::string(VALUE_DECLARATION));
        }
    }
    for(int i = (type == DECLARATION ? std::string(VALUE_DECLARATION).size() : 0 );i<tokens[offset].size();i++)
    {
        if(!inAlphabet(tokens[offset][i]) && tokens[offset][i]!=VALUE_DECLARATION[0])
        {
            if(type == DECLARATION)
            {
                throw std::invalid_argument("[Parsing value] Expected a valid declaration name after "+std::string(VALUE_DECLARATION));
            }
            return 0;
        }
        if(type==DIRECT)
        {
            if(tokens[offset][i]<'0' || tokens[offset][i]>'9')
            {
                type = REFERENCE;
            }
        }

    }
    value = tokens[offset];
    if(value==KW_MOV || value==KW_CARRY || value == KW_FLAG || value == KW_TIMES)
    {
        return 0;
    }
    if(type == DECLARATION)
    {
        std::reverse(value.begin(), value.end());
        for(int i=0;i<std::string(VALUE_DECLARATION).size();i++)
        {
            value.pop_back();
        }
        std::reverse(value.begin(), value.end());
    }
    return 1;
}

const std::string &Value::getValue() const {
    return value;
}

Value::Type Value::getType() const {
    return type;
}
