//
// Created by player402 on 30.03.25.
//

#include "Program.h"
#include "Comment.h"
#include "Instruction.h"
#include "Hook.h"
#include <algorithm>
#include <stdexcept>

unsigned int Program::match(std::vector<std::string> &tokens, unsigned int offset) {
    unsigned int sum = 0;
    for(unsigned int i=offset;i<tokens.size();)
    {
        unsigned int maxMatch=0;
        Pattern* comment = new Comment;
        Pattern* instruction = new Instruction;
        Pattern* hook = new Hook;
        unsigned int hookMatch;
        unsigned int instructionMatch;
        unsigned int commentMatch;
        try {
            hookMatch = hook->match(tokens, i);
            instructionMatch = instruction->match(tokens, i);
            commentMatch = comment->match(tokens, i);
        }
        catch(std::exception& e)
        {
            delete comment;
            delete instruction;
            delete hook;
            throw std::invalid_argument("[Parsing program] Syntax error on "+tokens[i]+" (token "+std::to_string(i)+"): "+std::string(e.what()));
        }

        maxMatch = std::max(std::max(hookMatch, commentMatch), instructionMatch);
        if(maxMatch==0)
        {
            delete comment;
            delete instruction;
            delete hook;
            throw std::invalid_argument("[Parsing program] Syntax error on "+tokens[i]+" (token "+std::to_string(i)+"): unrecognized pattern");
        }
        if(maxMatch == hookMatch)
        {
            delete comment;
            delete instruction;
            patterns.push_back(hook);
        }
        else if(maxMatch == instructionMatch)
        {
            delete comment;
            delete hook;
            patterns.push_back(instruction);
        }
        else if(maxMatch == commentMatch)
        {
            delete instruction;
            delete hook;
            delete comment;
        }
        i+=maxMatch;
        sum+=maxMatch;
    }

    return sum;
}
