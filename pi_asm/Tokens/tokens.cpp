//
// Created by player402 on 30.03.25.
//

#include "tokens.h"

bool inAlphabet(char x)
{
    if(x>='a' && x<='z')
    {
        return true;
    }
    if(x>='0' && x<='9')
    {
        return true;
    }
    if(x>='A' && x<='Z')
    {
        return true;
    }
    if(x=='_')
    {
        return true;
    }
    if(x=='-')
    {
        return true;
    }
    if(x=='.')
    {
        return true;
    }
    return false;
}