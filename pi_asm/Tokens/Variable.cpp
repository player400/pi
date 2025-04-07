//
// Created by player402 on 07.04.25.
//

#include <stdexcept>
#include "Variable.h"
#include "Value.h"

unsigned int Variable::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset+1 >= tokens.size())
    {
        return 0;
    }
    unsigned int length=0;
    while(true)
    {
        auto* value = new Value;
        unsigned int increment;
        try
        {
            increment = value->match(tokens, offset+length);
            length+=increment;
        }
        catch(std::exception& e)
        {
            delete value;
            throw std::invalid_argument("[Parsing variable declaration] Syntax error: "+std::string(e.what()));
        }
        if(length==0)
        {
            delete value;
            return 0;
        }
        if(increment==0)
        {
            delete value;
            throw std::invalid_argument("[Parsing variable declaration] Syntax error: Expected another value after the coma.");
        }
        patterns.push_back(value);
        if(offset+length > tokens.size())
        {
            return 0;
        }
        if(tokens[offset+length] == KW_TIMES)
        {
            length++;
            if(offset + length+1 > tokens.size())
            {
                throw std::invalid_argument("[Parsing variable declaration] Syntax error: Expected a value after the TIMES keyword.");
            }
            auto* timesValue = new Value;
            unsigned int timesValueMatch;
            try
            {
                timesValueMatch = timesValue->match(tokens, offset+ length);
            }
            catch(std::exception& e)
            {
                delete timesValue;
                throw std::invalid_argument("[Parsing variable declaration] Syntax error after the TIMES keyword, expected a value: "+std::string(e.what()));
            }
            if(timesValueMatch == 0)
            {
                delete timesValue;
                throw std::invalid_argument("[Parsing variable declaration] Syntax error after the TIMES keyword, expected a value.");
            }
            times = timesValue;
            length++;
            if(tokens[offset+length] != SEMICOLON)
            {
                delete timesValue;
                throw std::invalid_argument("[Parsing variable declaration] Syntax error: Expected a semicolon at the end of the line.");
            }
            return length+1;
        }
        else if(tokens[offset+length] == SEMICOLON)
        {
            return length+1;
        }
        else if(tokens[offset+length] == COMA)
        {
            length++;
        }
        else
        {
            return 0;
        }
    }
}

Variable::~Variable() {
    for(int i=0;i<patterns.size();i++)
    {
        delete patterns[i];
    }
    delete times;
}
