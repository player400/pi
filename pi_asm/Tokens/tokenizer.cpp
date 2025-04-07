//
// Created by player402 on 07.04.25.
//
#include <istream>
#include "tokenizer.h"
#include "tokenizer.h"
#include "tokens.h"

bool isWhitespace(char x) {
    if (x == '\t')
    {
        return true;
    }
    if (x == ' ')
    {
        return true;
    }
    if(x == '\n')
    {
        return true;
    }
    return false;

}

bool isTokenContinuation(std::string current, char x)
{
    current.push_back(x);
    std::string operators [] = {
            COMMENT,
            COLON,
            SEMICOLON,
            PARENTHESIS_C,
            PARENTHESIS_O,
            COMA,
            OP_ADD,
            OP_MUL,
            OP_NOT
    };

    for (std::string& op : operators)
    {
        if(op.find(current) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}

void tokenize(const std::vector<char>& stream, std::vector<std::string>& tokens, std::vector<int>&lines)
{
    enum State
    {
        INITIAL,
        OPERATOR,
        WORD,
    };

    std::string currentToken;

    State currentState = INITIAL;
    int lineCounter = 1;

    for(int i=0;i<stream.size();i++)
    {
        char x = stream[i];

        switch(currentState)
        {
            case INITIAL:
            {
                if(inAlphabet(x) || x == VALUE_DECLARATION[0])
                {
                    currentState = WORD;
                    currentToken.push_back(x);
                }
                else if(!isWhitespace(x))
                {
                    currentState = OPERATOR;
                    currentToken.push_back(x);
                }
                else if(x == '\n')
                {
                    lineCounter++;
                }
            } break;
            case OPERATOR:
            {
                if(inAlphabet(x) || x == VALUE_DECLARATION[0])
                {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                    currentState = WORD;
                    currentToken.push_back(x);
                    lines.push_back(lineCounter);
                }
                else if(isWhitespace(x))
                {
                    tokens.push_back(currentToken);
                    lines.push_back(lineCounter);
                    currentToken.clear();
                    currentState = INITIAL;
                    if(x=='\n')
                    {
                        lineCounter++;
                    }
                }
                else if(isTokenContinuation(currentToken, x))
                {
                    currentToken.push_back(x);
                }
                else
                {
                    tokens.push_back(currentToken);
                    lines.push_back(lineCounter);
                    currentToken.clear();
                    currentState = OPERATOR;
                    currentToken.push_back(x);
                }
            } break;
            case WORD:
            {
                if(inAlphabet(x))
                {
                    currentToken.push_back(x);
                }
                else if(x == VALUE_DECLARATION[0])
                {
                    tokens.push_back(currentToken);
                    lines.push_back(lineCounter);
                    currentToken.clear();
                    currentToken.push_back(x);
                }
                else if(isWhitespace(x))
                {
                    tokens.push_back(currentToken);
                    lines.push_back(lineCounter);
                    currentToken.clear();
                    currentState = INITIAL;
                    if(x=='\n')
                    {
                        lineCounter++;
                    }
                }
                else
                {
                    tokens.push_back(currentToken);
                    lines.push_back(lineCounter);
                    currentToken.clear();
                    currentState = OPERATOR;
                    currentToken.push_back(x);
                }
            } break;
        }

    }

}


void input(std::istream& source, std::vector<char>& stream)
{
    char a;
    while(source>>a)
    {
        stream.push_back(a);
    }
}