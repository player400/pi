//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "FLAG.h"
#include "Value.h"
#include "Expression.h"

unsigned int FLAG::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset>=tokens.size())
    {
        return 0;
    }
    if(tokens[offset]!=KW_FLAG)
    {
        return 0;
    }
    Pattern* flag = new Value;
    if(!flag->match(tokens, offset+1))
    {
        delete flag;
        throw std::invalid_argument("[Parsing FLAG] Syntax error on "+tokens[offset+1]+": Expected a value.");
    }
    if(offset+2 >= tokens.size() || tokens[offset+2]!=COMA)
    {
        delete flag;
        throw std::invalid_argument("[Parsing FLAG] Syntax error on "+tokens[offset+2]+": Expected a coma after first argument.");
    }
    Pattern* value = new Expression;
    unsigned int tokenMatch;
    try {
        tokenMatch = value->match(tokens, offset + 3);
    }
    catch(std::exception& e)
    {
        delete flag;
        delete value;
        throw std::invalid_argument("[Parsing FLAG] Syntax error on "+tokens[offset+3]+": Expected a valid expression: "+std::string(e.what()));
    }
    if(!tokenMatch)
    {
        delete flag;
        delete value;
        throw std::invalid_argument("[Parsing FLAG] Syntax error on "+tokens[offset+3]+": Expected a valid expression.");
    }
    else
    {
        patterns.push_back(flag);
        patterns.push_back(value);
    }
    if(offset+3 >= tokens.size() || tokens[offset+3+tokenMatch]!=SEMICOLON)
    {
        delete flag;
        delete value;
        throw std::invalid_argument("[Parsing FLAG] Syntax error on "+tokens[offset+3+tokenMatch]+": Expected a semicolon.");
    }
    return 4 + tokenMatch;
}
