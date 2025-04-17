//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_ENTITY_H
#define PI_ASM_ENTITY_H

#include <functional>
#include <cstdint>
#include <ostream>
#include "Writer/Writer.h"


class Entity {
public:

    enum Architecture
    {
        BIT4,
        BIT8
    };

protected:
    Writer& writer;
    Architecture architecture;

public:
    virtual void write() = 0;

    Entity(Writer &writer, Architecture architecture);
};


#endif //PI_ASM_ENTITY_H
