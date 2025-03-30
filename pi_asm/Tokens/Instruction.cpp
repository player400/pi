//
// Created by player402 on 30.03.25.
//

#include <stdexcept>
#include "Instruction.h"
#include "MOV.h"
#include "FLAG.h"

unsigned int Instruction::match(std::vector<std::string> &tokens, unsigned int offset) {
    Pattern *mov = new MOV;
    Pattern *flag = new FLAG;
    unsigned int flagMatch;
    unsigned int movMatch;
    try {
        flagMatch = flag->match(tokens, offset);
        movMatch = mov->match(tokens, offset);
    }
    catch (std::exception &e) {
        delete flag;
        delete mov;
        throw std::invalid_argument(
                "[Parsing instruction] Syntax error on " + tokens[offset] + ": " + std::string(e.what()));
    }
    if (flagMatch == 0 && movMatch == 0) {
        delete flag;
        delete mov;
        return 0;
    }
    if (flagMatch > movMatch) {
        delete mov;
        patterns.push_back(flag);
        return flagMatch;
    }
    else
    {
        delete flag;
        patterns.push_back(mov);
        return movMatch;
    }
}
