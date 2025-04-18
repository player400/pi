//
// Created by player402 on 04.10.24.
//

#ifndef PI_VM_PROGRAMARGUMENTPROCESSING_H
#define PI_VM_PROGRAMARGUMENTPROCESSING_H

#include <string>
#include <vector>
#include <stdexcept>


enum Options
{
    HEX_FILE,
    DECIMAL_FILE,
    BINARY_FILE,
    BIT4,
    BIT8,
    UNRECOGNIZED,

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
        {BIT4, "4", 1},
        {BIT8, "8", 1},
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
                throw std::invalid_argument("Program arguments parser: Program option "+options[options.size()-1].token+" only takes "
                +std::to_string(optionTypes[options[options.size()-1].id].argumentCount) + " arguments. Argument '"+option+"' is not needed (argument "+std::to_string(i)+" - check spaces).");
            }
            else
            {
                throw std::invalid_argument("Program arguments parser: Program option '"+option+"' does not exist."+"Argument '"+option+"' is not needed (argument "+std::to_string(i)+" - check spaces).");
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


void applyProgramArguments(ExecutableFileType& fileType, std::string& outputFileName, Entity::Architecture& architecture, std::string& inputFileName, int argc, char* argv[])
{
    fileType = NONE;
    std::vector<ParsedOption>options;
    parseProgramArguments(argc,argv, options);
    for(auto & option : options)
    {
        if(option.type==BINARY_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: Specify a single output file format and name.");
            }
            fileType = BINARY;
            outputFileName = option.arguments[0];
        }
        if(option.type==HEX_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: Specify a single output file format and name.");
            }
            fileType = HEXADECIMAL;
            outputFileName = option.arguments[0];
        }
        if(option.type==DECIMAL_FILE)
        {
            if(fileType!=NONE)
            {
                throw std::invalid_argument("General: Specify a single output file format and name.");
            }
            fileType = DECIMAL;
            outputFileName = option.arguments[0];
        }
        if(option.type == BIT4)
        {
            architecture = Entity::BIT4;
            inputFileName = option.arguments[0];
        }
        if(option.type == BIT8)
        {
            architecture = Entity::BIT8;
            inputFileName = option.arguments[0];
        }
    }
}

#endif //PI_VM_PROGRAMARGUMENTPROCESSING_H
