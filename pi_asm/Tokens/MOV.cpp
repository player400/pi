//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "MOV.h"
#include "Value.h"

unsigned int MOV::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset >= tokens.size())
    {
        return 0;
    }
    if(tokens[offset]!=KW_MOV)
    {
        return 0;
    }
    Pattern* destination = new Value;
    if(!destination->match(tokens, offset+1))
    {
        delete destination;
        throw std::invalid_argument("[Parsing MOV] Syntax error on "+tokens[offset+1]+": Expected a value.");
    }
    if(offset+2>=tokens.size() || tokens[offset+2]!=COMA)
    {
        delete destination;
        throw std::invalid_argument("[Parsing MOV] Syntax error on "+tokens[offset+2]+": Expected a coma after first argument.");
    }
    Pattern* source = new Value;
    if(!source->match(tokens, offset+3))
    {
        delete destination;
        delete source;
        throw std::invalid_argument("[Parsing MOV] Syntax error on "+tokens[offset+3]+": Expected a second argument after the coma.");
    }
    if(offset+4 >= tokens.size() || tokens[offset+4]!=SEMICOLON)
    {
        delete destination;
        delete source;
        throw std::invalid_argument("[Parsing MOV] Syntax error on "+tokens[offset+4]+": Expected a semicolon after the instruction.");
    }
    patterns.push_back(destination);
    patterns.push_back(source);
    return 5;
}
