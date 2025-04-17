//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_PATTERN_H
#define PI_ASM_PATTERN_H

#include "tokens.h"
#include <vector>
#include <string>

class Pattern {
protected:
    std::vector<Pattern*> patterns;

    virtual bool isToken();
public:

    virtual unsigned int match(std::vector<std::string> &tokens, unsigned int offset) = 0;

    Pattern& operator[](unsigned int position);

    unsigned int size();

};


#endif //PI_ASM_PATTERN_H
