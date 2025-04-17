//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_ASSEMBLY_H
#define PI_ASM_ASSEMBLY_H


#include <vector>
#include "Entity.h"
#include "../Tokens/Program.h"
#include "../Tokens/Instruction.h"
#include "../Tokens/Value.h"

class Assembly {
private:
    Writer& writer;
    std::vector<Entity*> entities;
    Entity::Architecture architecture;
    std::unordered_map<std::string, int>symbolMap;

    int memoryCellsPerInstruction;
    int maxRegistryAddress;
    int maxAddress;
    int maxExtendedAddress;
    int maxFlagAddress;
    int signature;

    void populateSymbolMap(Program& program);
    void generateEntities(Program& program);
    int getTrueValue(Value* value);
    void write();

public:
    void generateByteCode(Program& program);



    void writeToFile(std::string& fileName);

    Assembly(Entity::Architecture architecture, Writer& writer);

    ~Assembly();
};


#endif //PI_ASM_ASSEMBLY_H
