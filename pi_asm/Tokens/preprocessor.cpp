//
// Created by player402 on 07.04.25.
//
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "preprocessor.h"
#include "tokens.h"


void preprocess(std::vector<std::string>&tokens)
{
    std::unordered_map<std::string, std::string> macros;
    std::vector<std::string>new_tokens;

    for(int i=0;i<tokens.size();i++)
    {
        if(tokens[i]==KW_DEFINE)
        {
            if(i+2 >= tokens.size())
            {
                throw std::invalid_argument("[Pre-processing] Syntax error: Expected at least 2 tokens after the keyword DEFINE");
            }
            macros.insert({tokens[i+1], tokens[i+2]});
            i+=2;
        }
        else
        {
            new_tokens.push_back(tokens[i]);
        }
    }
    tokens.clear();
    for(int i=0;i<new_tokens.size();i++)
    {
        auto element = macros.find(new_tokens[i]);
        if(element != macros.end())
        {
            tokens.push_back(element->second);
        }
        else
        {
            tokens.push_back(new_tokens[i]);
        }
    }

}