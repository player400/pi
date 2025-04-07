//
// Created by player402 on 30.03.25.
//

#include "Program.h"
#include "Comment.h"
#include "Instruction.h"
#include "Hook.h"
#include "Variable.h"
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
        Pattern* variable = new Variable;
        unsigned int hookMatch;
        unsigned int instructionMatch;
        unsigned int commentMatch;
        unsigned int variableMatch;
        try {
            hookMatch = hook->match(tokens, i);
            instructionMatch = instruction->match(tokens, i);
            commentMatch = comment->match(tokens, i);
            variableMatch = variable->match(tokens, i);
        }
        catch(std::exception& e)
        {
            delete comment;
            delete instruction;
            delete hook;
            delete variable;
            throw std::invalid_argument(fileName+": [Parsing file] Syntax error on line "+std::to_string(lines[i])+": "+std::string(e.what()));
        }

        maxMatch = std::max(std::max(std::max(hookMatch, commentMatch), instructionMatch), variableMatch);
        if(maxMatch==0)
        {
            delete comment;
            delete instruction;
            delete hook;
            delete variable;
            throw std::invalid_argument(fileName+": [Parsing file] Syntax error on line "+std::to_string(lines[i])+": unrecognized pattern on '"+tokens[i]+"'");
        }
        if(maxMatch == hookMatch)
        {
            delete comment;
            delete instruction;
            delete variable;
            patterns.push_back(hook);
        }
        else if(maxMatch == instructionMatch)
        {
            delete comment;
            delete hook;
            delete variable;
            patterns.push_back(instruction);
        }
        else if(maxMatch == variableMatch)
        {
            delete hook;
            delete comment;
            delete instruction;
            patterns.push_back(variable);
        }
        else if(maxMatch == commentMatch)
        {
            delete instruction;
            delete hook;
            delete comment;
            delete variable;
        }
        i+=maxMatch;
        sum+=maxMatch;
    }

    return sum;
}

Program::Program(std::string fileName, std::vector<int> &lines):lines(lines) {
    this->fileName = fileName;
}
