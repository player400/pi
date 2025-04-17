//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_BINARYWRITER_H
#define PI_ASM_BINARYWRITER_H


#include "Writer.h"

class BinaryWriter : public Writer{
public:
    void pushBack(uint8_t byte) override;
};


#endif //PI_ASM_BINARYWRITER_H
