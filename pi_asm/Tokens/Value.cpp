//
// Created by player402 on 30.03.25.
//

#include "Value.h"

unsigned int Value::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(offset>=tokens.size())
    {
        return 0;
    }
    for(int i=0;i<tokens[offset].size();i++)
    {
        if(!inAlphabet(tokens[offset][i]))
        {
            return 0;
        }
    }
    value = tokens[offset];
    return 1;
}
