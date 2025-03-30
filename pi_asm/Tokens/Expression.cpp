//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "Expression.h"
#include "Logic.h"

unsigned int Expression::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset>=tokens.size())
    {
        return 0;
    }
    unsigned int sum = 0;
    bool parenthesis = false;
    if(tokens[offset]==OP_NOT)
    {
        offset++;
        sum++;
        negate = true;
    }
    if(offset < tokens.size() && tokens[offset] == PARENTHESIS_O)
    {
        parenthesis = true;
        offset++;
        sum++;
    }
    Pattern* logic1 = new Logic;
    unsigned int logic1Match;
    try {
        logic1Match = logic1->match(tokens, offset);
    }
    catch(std::exception& e)
    {
        delete logic1;
        throw std::invalid_argument("[Parsing expression] Syntax error: "+std::string(e.what()));
    }
    if(!logic1Match)
    {
        if(parenthesis || negate)
        {
            delete logic1;
            throw std::invalid_argument("[Parsing expression] Syntax error: expected a logical value after '(' or '~'");
        }
        else
        {
            delete logic1;
            return 0;
        }
    }
    else
    {
        sum+=logic1Match;
        offset+=logic1Match;
        patterns.push_back(logic1);
    }
    unsigned int addOnsMatch;
    try {
        addOnsMatch = matchAddOns(tokens, offset);
    }
    catch(std::exception& e)
    {
        delete logic1;
        throw std::invalid_argument("[Parsing expression] Syntax error: "+std::string(e.what()));
    }
    sum+=addOnsMatch;
    offset+=addOnsMatch;
    if(!parenthesis && negate && addOnsMatch)
    {
        throw std::invalid_argument("[Parsing expression] Syntax error: You can only negate the entire expression, not 1 value. If that's what you wanted to do - use parenthesis");
    }
    if(parenthesis)
    {
        if(offset>=tokens.size() || tokens[offset]!=PARENTHESIS_C)
        {
            throw std::invalid_argument("[Parsing expression] Syntax error: Unclosed parenthesis!");
        }
        else
        {
            sum+=1;
            offset+=1;
        }
    }
    return sum;
}

unsigned int Expression::matchAddOns(std::vector<std::string> &tokens, unsigned int offset) {
    unsigned int sum = 0;
    for(int i=0;i<2;i++)
    {
        if(offset+sum >= tokens.size() || (tokens[offset+sum]!=OP_ADD && tokens[offset+sum]!=OP_MUL))
        {
            return sum;
        }
        else
        {
            OperationType newType;
            if(tokens[offset+sum]==OP_ADD)
            {
                newType = ADD;
            }
            else
            {
                newType = MUL;
            }
            if(i>0)
            {
                if(newType != type)
                {
                    throw std::invalid_argument("[Parsing expression] Syntax error: All operations performed on the values must be the same (either 2 '+' or 2 '*')");
                }
            }
            sum++;
        }
        Pattern* logic = new Logic;
        unsigned int logicMatch;
        try
        {
            logicMatch = logic->match(tokens, offset+sum);
        }
        catch(std::exception& e)
        {
            delete logic;
            throw std::invalid_argument("[Parsing expression] Syntax error: "+std::string(e.what()));
        }
        if(!logicMatch)
        {
            delete logic;
            throw std::invalid_argument("[Parsing expression] Syntax error: expected a logical value after an operator");
        }
        else
        {
            patterns.push_back(logic);
        }
        sum+=logicMatch;
    }


    return sum;
}
