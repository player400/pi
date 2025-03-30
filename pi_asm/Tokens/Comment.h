//
// Created by player402 on 30.03.25.
//

#ifndef PI_ASM_COMMENT_H
#define PI_ASM_COMMENT_H


#include "Pattern.h"

class Comment : public Pattern{
public:
    unsigned int match(std::vector<std::string> &tokens, unsigned int offset) override;
};


#endif //PI_ASM_COMMENT_H
