//
// Created by player402 on 17.04.25.
//

#include "Assembly.h"
#include "../Tokens/Variable.h"
#include "../Tokens/Hook.h"
#include "../Tokens/MOV.h"
#include "../Tokens/Expression.h"
#include "../Tokens/Logic.h"
#include "InstructionMOV.h"
#include "InstructionFLAG.h"
#include "Data.h"
#include <fstream>
#include <cstring>

Assembly::Assembly(Entity::Architecture architecture, Writer &writer):architecture(architecture),writer(writer) {
    if(architecture == Entity::BIT8)
    {
        maxRegistryAddress = 15;
        memoryCellsPerInstruction = 2;
        maxAddress = 255;
        maxExtendedAddress = 1023;
        maxFlagAddress = 3;
        signature = 8;
    }
    else if(architecture==Entity::BIT4)
    {
        maxRegistryAddress = 3;
        memoryCellsPerInstruction = 2;
        maxAddress = 15;
        maxExtendedAddress = 15;
        maxFlagAddress = 2;
        signature = 4;
    }
}

void Assembly::generateByteCode(Program &program) {
    populateSymbolMap(program);
    generateEntities(program);
    write();
}

void Assembly::writeToFile(std::string& fileName) {
    std::ofstream outputFile(fileName);
    if(outputFile.fail())
    {
        throw std::invalid_argument("Error while opening output file: "+std::string(strerror(errno)));
    }
    outputFile.clear();
    writer.writeAll(outputFile);
    outputFile.close();
}

void Assembly::populateSymbolMap(Program &program) {
    symbolMap.clear();
    unsigned int memoryCellCounter = 0;
    for(int i=0;i<program.size();i++)
    {
        if(dynamic_cast<Instruction*>(&program[i]))
        {
            if(dynamic_cast<MOV*>(&program[i][0]))
            {
                for(int j=0;j<program[i][0].size();j++) {
                    auto value = (Value *) (&program[i][0][j]);
                    if (value->getType() == Value::DECLARATION)
                    {
                        symbolMap.insert({value->getValue(), memoryCellCounter + 1});
                        break;
                    }
                }
            }
            else //This is a FLAG instruction
            {
                auto logicalValue = (Expression*)(&program[i][0][1]);
                for(int j=0;j<logicalValue->size();j++)
                {
                    auto value = (Logic*)(&program[i][0][1][j]);
                    if(value->getType() == Logic::ADDRESS)
                    {
                        auto innerValue = (Value*)(&program[i][0][1][j][0]);
                        if(innerValue->getType()==Value::DECLARATION)
                        {
                            symbolMap.insert({innerValue->getValue(), memoryCellCounter+1});
                        }
                    }
                }
            }
            memoryCellCounter+=memoryCellsPerInstruction;
        }
        if(dynamic_cast<Variable*>(&program[i])){
            auto variable = dynamic_cast<Variable*>(&program[i]);

            Value* times = variable->getTimes();
            if(times == nullptr)
            {
                memoryCellCounter+= variable->size();
            }
            else if(times->getType()==Value::DECLARATION)
            {
                throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": TIMES keyword cannot be followed by a value declaration - this cannot be evaluated during runtime.");
            }
            else if(times->getType()==Value::REFERENCE)
            {
                auto actualValue = symbolMap.find(times->getValue());
                if(actualValue==symbolMap.end())
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Value following the TIMES keyword may be a reference, but it must be declared before this expression.");
                }
                memoryCellCounter += variable->size()*actualValue->second;
            }
            else
            {
                memoryCellCounter += variable->size()*stoi(times->getValue());
            }
        }
        if(dynamic_cast<Hook*>(&program[i]))
        {
            auto* value = (Value*)(&program[i][0]);
            if(value->getType()==Value::DIRECT)
            {
                throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Name cannot be a number.");
            }
            symbolMap.insert({value->getValue(), memoryCellCounter});
        }
    }
}

void Assembly::generateEntities(Program &program) {
    for(int i =0;i<program.size();i++)
    {
        if(dynamic_cast<Instruction*>(&program[i]))
        {
            if(dynamic_cast<MOV*>(&program[i][0]))
            {
                int value1;
                int value2;
                try
                {
                    value1 = getTrueValue((Value*)(&program[i][0][0]));
                    value2 = getTrueValue((Value*)(&program[i][0][1]));
                }
                catch(std::exception& e)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Error while evaluating values: "+std::string(e.what()));
                }
                if(value1 > maxRegistryAddress && value2 > maxRegistryAddress)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": You cannot MOV from memory to memory - one of the values must be a registry number, not an address");
                }
                if(value1 > maxExtendedAddress || value2 > maxExtendedAddress)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Memory address must not be higher than "+std::to_string(maxExtendedAddress));
                }
                int source;
                int destination;
                bool reverse;
                if(value2>maxRegistryAddress)
                {
                    source = value2;
                    destination = value1;
                    reverse = false;
                }
                else
                {
                    source = value1;
                    destination = value2;
                    reverse = true;
                }
                auto mov = new InstructionMOV(writer, architecture, destination, reverse, source);
                entities.push_back(mov);
            }
            else //This is a FLAG instruction
            {
                int flag;
                try
                {
                    flag = getTrueValue((Value*)(&program[i][0][0]));
                }
                catch(std::exception& e)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Error while evaluating value of the flag number: "+std::string(e.what()));
                }
                if(flag>maxFlagAddress)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Flag number must not be higher than "+std::to_string(maxFlagAddress));
                }
                auto expression = (Expression*)(&program[i][0][1]);
                bool negate = expression->isNegate();
                bool value;
                InstructionFLAG::Operation operation;
                auto opType = expression->getType();
                if(opType == Expression::ADD)
                {
                    value = false;
                    operation = InstructionFLAG::ADD;
                }
                if(opType == Expression::MUL)
                {
                    value = true;
                    operation = InstructionFLAG::MULTIPLY;
                }
                bool carry = false;
                int address = 0;
                bool memory = false;
                for(int j=0;j<expression->size();j++)
                {
                    auto logic = dynamic_cast<Logic*>(&((*expression)[j]));
                    if(logic->getType()==Logic::CARRY)
                    {
                        carry = true;
                    }
                    if(logic->getType()==Logic::ADDRESS)
                    {
                        memory = true;
                        try
                        {
                            address = getTrueValue((Value*)(&program[i][0][1][j][0]));
                        }
                        catch(std::exception& e)
                        {
                            throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Error while evaluating address in the FLAG instruction: "+std::string(e.what()));
                        }
                        if(address > maxAddress)
                        {
                            throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Memory address must not be higher than "+std::to_string(maxAddress));
                        }
                        if(architecture == Entity::BIT4 && address!=3)
                        {
                            throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": For the 4-bit PI architecture address given in the FLAG instruction must be 3");
                        }
                    }
                    if(logic->getType()==Logic::BOOLEAN)
                    {
                        value = logic->getValue();
                    }
                }
                auto flagInstruction = new InstructionFLAG(writer, architecture, flag, value, carry, memory, address, negate, operation);
                entities.push_back(flagInstruction);
            }
        }
        if(dynamic_cast<Variable*>(&program[i])){
            auto variable = dynamic_cast<Variable*>(&program[i]);
            int times = 1;
            if(variable->getTimes()!= nullptr)
            {
                try
                {
                    times = getTrueValue((Value*)variable->getTimes());
                }
                catch(std::exception& e)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Error while evaluating the value given after the TIMES keyword: "+std::string(e.what()));
                }
            }
            auto data = new Data(writer, architecture, times);
            for(int j=0;j<variable->size();j++)
            {
                int byte;
                try
                {
                    byte = getTrueValue((Value*)(&program[i][j]));
                }
                catch(std::exception& e)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Error while evaluating a byte given in a data statement: "+std::string(e.what()));
                }
                if(times > maxAddress)
                {
                    throw std::invalid_argument("Semantic error on line "+std::to_string(program.getPatternLine(i))+": Bytes given in the data statement must have value non greater than "+std::to_string(maxAddress));
                }
                data->pushBack(byte);
            }
            entities.push_back(data);
        }
    }
}

int Assembly::getTrueValue(Value *value) {
    auto type = value->getType();
    if(type == Value::DECLARATION)
    {
        return maxAddress;
    }
    else if(type == Value::DIRECT)
    {
        return stoi(value->getValue());
    }
    else if(type == Value::REFERENCE)
    {
        auto symbol = symbolMap.find(value->getValue());
        if(symbol == symbolMap.end())
        {
            throw std::invalid_argument("Referenced value '"+value->getValue()="' has not been declared.");
        }
        return symbol->second;
    }
}

Assembly::~Assembly() {
    for(int i=0;i<entities.size();i++)
    {
        delete entities[i];
    }
}

void Assembly::write() {
    writer.pushBack(signature);
    for(auto& entity : entities)
    {
        entity->write();
    }
}
