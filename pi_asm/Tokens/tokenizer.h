//
// Created by player402 on 07.04.25.
//

#ifndef PI_ASM_TOKENIZER_H
#define PI_ASM_TOKENIZER_H

#include <vector>
#include <string>

void tokenize(const std::vector<char>& stream, std::vector<std::string>& tokens);


void input(std::istream& source, std::vector<char>& stream);


#endif //PI_ASM_TOKENIZER_H
