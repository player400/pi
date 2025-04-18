#include <iostream>
#include <vector>
#include "Tokens/Program.h"
#include "Tokens/tokenizer.h"
#include "Tokens/preprocessor.h"
#include "Assembly/Assembly.h"
#include "Assembly/Writer/BinaryWriter.h"
#include <fstream>
#include <cstring>

enum ExecutableFileType
{
    NONE,
    BINARY,
    HEXADECIMAL,
    DECIMAL,
};

#include "ProgramArgumentProcessing.h"
#include "Assembly/Writer/HexadecimalWriter.h"
#include "Assembly/Writer/DecimalWriter.h"

void assemblyFile(std::string &inputFileName, std::string& outputFileName, ExecutableFileType outputFileType, Entity::Architecture architecture)
{
    std::vector<char>stream;
    std::ifstream file(inputFileName);
    if(file.fail())
    {
        throw std::invalid_argument("Error while opening input file: "+std::string(strerror(errno)));
    }
    file.unsetf(std::ios_base::skipws);
    input(file, stream);

    std::vector<std::string> tokens;
    std::vector<int> lines;

    tokenize(stream, tokens, lines);
    preprocess(tokens);

    Program program(inputFileName, lines);
    program.match(tokens, 0);

    Writer* writer;
    switch(outputFileType)
    {

        case NONE:
            throw std::invalid_argument("General: You must specify output file type");
            break;
        case BINARY:
            writer = new BinaryWriter;
            break;
        case HEXADECIMAL:
            writer = new HexadecimalWriter;
            break;
        case DECIMAL:
            writer = new DecimalWriter;
            break;
    }

    Assembly assembly(architecture, *writer);
    assembly.generateByteCode(program);
    assembly.writeToFile(outputFileName);
}

int main(int argc, char** argv) {

    std::string inputFileName;
    std::string outputFileName;
    ExecutableFileType outputFileType;
    Entity::Architecture architecture;
    try
    {
        applyProgramArguments(outputFileType, outputFileName, architecture, inputFileName, argc, argv);
    }
    catch(std::exception& e)
    {
        std::cerr<<"Error while parsing program arguments: "<<e.what()<<std::endl;
    }
    try
    {
        assemblyFile(inputFileName, outputFileName, outputFileType, architecture);
    }
    catch(std::exception& e)
    {
        std::cerr<<"Build failed: "<<e.what()<<std::endl;
    }
    return 0;
}
