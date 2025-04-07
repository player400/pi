#include <iostream>
#include <vector>
#include "Tokens/Program.h"
#include "Tokens/tokenizer.h"
#include "Tokens/preprocessor.h"
#include <fstream>

int main() {
    std::vector<std::string> tokens;
    std::vector<int> lines;
    std::vector<char>stream;
    std::ifstream file("test.pi");
    file.unsetf(std::ios_base::skipws);
    input(file, stream);

    tokenize(stream, tokens, lines);
    preprocess(tokens);
    Program program("test.pi", lines);
    program.match(tokens, 0);
    return 0;
}
