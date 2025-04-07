#include <iostream>
#include <vector>
#include "Tokens/Program.h"
#include "Tokens/tokenizer.h"
#include <fstream>

int main() {
    std::vector<std::string> tokens;
    std::vector<char>stream;
    std::ifstream file("test.pi");
    file.unsetf(std::ios_base::skipws);
    input(file, stream);

    tokenize(stream, tokens);

    Program program;
    program.match(tokens, 0);
    return 0;
}
