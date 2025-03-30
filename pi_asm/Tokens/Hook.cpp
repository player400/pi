//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "Hook.h"
#include "Value.h"

unsigned int Hook::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(tokens.size()-1 == offset)
    {
        return 0;
    }
    if(tokens[offset+1]!=COLON)
    {
        return 0;
    }
    Pattern* value = new Value;
    try {
        if (value->match(tokens, offset)) {
            patterns.push_back(value);
            return 2;
        }
    }
    catch(std::exception& e)
    {
        delete value;
        throw std::invalid_argument("[Parsing a hook] Syntax error on "+tokens[offset]+": "+std::string(e.what()));
    }
    delete value;
    return 0;
}
