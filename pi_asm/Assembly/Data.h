//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_DATA_H
#define PI_ASM_DATA_H


#include "Entity.h"

class Data : public Entity {

private:
    std::vector<uint8_t> bytes;
    int times;

public:
    void pushBack(uint8_t byte);
    void write() override;
    Data(Writer &writer, Architecture architecture, int times);
};


#endif //PI_ASM_DATA_H
