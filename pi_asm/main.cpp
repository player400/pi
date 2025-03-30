#include <iostream>
#include <vector>
#include "Tokens/Program.h"

int main() {
    std::vector<std::string> tokens;
    tokens.push_back("MOV");
    tokens.push_back("2");
    tokens.push_back(",");
    tokens.push_back("45");
    tokens.push_back(";");
    tokens.push_back("//");
    tokens.push_back("grg43t3f");
    tokens.push_back(",");
    tokens.push_back("45");
    tokens.push_back(";");
    tokens.push_back("FLAG");
    tokens.push_back("8");
    tokens.push_back(",");
    tokens.push_back("~");
    tokens.push_back("(");
    tokens.push_back("CARRY");
    tokens.push_back("+");
    tokens.push_back("FALSE");
    tokens.push_back("+");
    tokens.push_back("false");
    tokens.push_back(")");
    tokens.push_back(";");
    Program program;
    program.match(tokens, 0);
    return 0;
}
