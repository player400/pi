//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "Comment.h"

unsigned int Comment::match(std::vector<std::string> &tokens, unsigned int offset) {
    if(tokens[offset]!=COMMENT)
    {
        return 0;
    }
    for(unsigned int i=offset+1;i<tokens.size();i++)
    {
        if(tokens[i]==SEMICOLON)
        {
            return i-offset+1;
        }
    }
    throw std::invalid_argument("[Parsing comment] Syntax error: expected a semicolon at the end of the comment.");
}
