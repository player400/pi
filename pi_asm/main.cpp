#include <iostream>
#include <vector>
#include "Tokens/Program.h"
#include "Tokens/tokenizer.h"
#include "Tokens/preprocessor.h"
#include "Assembly/Assembly.h"
#include "Assembly/Writer/BinaryWriter.h"
#include <fstream>



void assemblyFile(std::string &fileName)
{
    std::vector<char>stream;
    std::ifstream file(fileName);
    file.unsetf(std::ios_base::skipws);
    input(file, stream);

    std::vector<std::string> tokens;
    std::vector<int> lines;

    tokenize(stream, tokens, lines);
    preprocess(tokens);

    Program program(fileName, lines);
    program.match(tokens, 0);

    Writer* writer = new BinaryWriter;

    Assembly assembly(Entity::BIT8, *writer);
    assembly.generateByteCode(program);
    std::string outputFile = "test.bin";
    assembly.writeToFile(outputFile);
}

int main() {

    std::string fileName = "test.pi";

    assemblyFile(fileName);
    return 0;
}
