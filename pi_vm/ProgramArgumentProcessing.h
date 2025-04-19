//
// Created by player402 on 04.10.24.
//

#ifndef PI_VM_PROGRAMARGUMENTPROCESSING_H
#define PI_VM_PROGRAMARGUMENTPROCESSING_H

#include <string>
#include <vector>
#include <stdexcept>
#include "programmer/ExecutableFileReader/ExecutableFileReader.h"

enum Options
{
    HEX_FILE,
    DECIMAL_FILE,
    BINARY_FILE,
    ARCHITECTURE,
    UNRECOGNIZED,
    DEBUG,
    PRINT_OUTPUT,
};

struct OptionType
{
    Options type;
    std::string token;
    int argumentCount;
};

struct ParsedOption
{
    Options type;
    std::vector<std::string>arguments;
    std::string token;
    int id;
};

const OptionType optionTypes[] = {
        {HEX_FILE, "h", 1},
        {DECIMAL_FILE, "d", 1},
        {BINARY_FILE, "b", 1},
        {ARCHITECTURE, "a", 1},
        {DEBUG, "debug", 0},
        {PRINT_OUTPUT, "p", 0},
        {UNRECOGNIZED, "[unrecognized option]", 0}
};


void parseProgramArguments(int argc, char* argv[], std::vector<ParsedOption>& options)
{
    for(int i=1;i<argc;i++)
    {
        std::string option = std::string(argv[i]);
        int j=0;
        Options type;
        do
        {
            type = optionTypes[j].type;
            if(option == '-'+optionTypes[j].token)
            {
                break;
            }
            j++;
        } while(type!=UNRECOGNIZED);    //Checking whether the string given fits any known pattern, if not - marked as unrecognized
        if(type==UNRECOGNIZED)
        {
            if(option[0]!='-')
            {
                throw std::invalid_argument("Program arguments parser: [option argument parsing] Program option "+options[options.size()-1].token+" only takes "
                +std::to_string(optionTypes[options[options.size()-1].id].argumentCount) + " arguments. Argument '"+option+"' is not needed (argument "+std::to_string(i)+" - check spaces).");
            }
            else
            {
                throw std::invalid_argument("Program arguments parser: [option parsing] Program option '"+option+"' does not exist."+"Argument '"+option+"' is not needed (argument "+std::to_string(i)+" - check spaces).");
            }
        }
        else
        {
            options.emplace_back();
            options[options.size()-1].type = type;
            options[options.size()-1].token = option;
            options[options.size()-1].id = j;
            for(int k=0;k<optionTypes[j].argumentCount;k++)
            {
                i++;
                options[options.size()-1].arguments.emplace_back(argv[i]);
            }
        }

    }
}


void applyProgramArguments(ExecutableFileType& fileType, std::string& fileName, int& architecture, bool& debug, bool& printOutput, int argc, char* argv[])
{
    fileType = NONE;
    std::vector<ParsedOption>options;
    parseProgramArguments(argc,argv, options);
    architecture = 8;
    debug = false;
    printOutput = false;
    for(auto & option : options)
    {
        if(option.type==BINARY_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: [determining program file type] You cannot import multiple files into one emulation.");
            }
            fileType = BINARY;
            fileName = option.arguments[0];
        }
        if(option.type==HEX_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: [determining program file type] You cannot import multiple files into one emulation.");
            }
            fileType = HEXADECIMAL;
            fileName = option.arguments[0];
        }
        if(option.type==DECIMAL_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: [determining program file type] You cannot import multiple files into one emulation.");
            }
            fileType = DECIMAL;
            fileName = option.arguments[0];
        }
        if(option.type == ARCHITECTURE)
        {
            architecture = stoi(option.arguments[0]);
        }
        if(option.type == DEBUG)
        {
            if(printOutput)
            {
                throw std::invalid_argument("General: [applying options] Options -debug and -p cannot be both used.");
            }
            debug = true;
        }
        if(option.type == PRINT_OUTPUT)
        {
            if(debug)
            {
                throw std::invalid_argument("General: [applying options] Options -debug and -p cannot be both used.");
            }
            printOutput = true;
        }
    }
}

#endif //PI_VM_PROGRAMARGUMENTPROCESSING_H
