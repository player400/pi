//
// Created by player402 on 18.04.25.
//

#ifndef PI_ASM_DECIMALWRITER_H
#define PI_ASM_DECIMALWRITER_H


#include <cstdint>
#include "Writer.h"

class DecimalWriter : public Writer{
public:
    void pushBack(uint8_t byte) override;
};


#endif //PI_ASM_DECIMALWRITER_H
