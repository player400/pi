//
// Created by player402 on 18.04.25.
//

#ifndef PI_ASM_HEXADECIMALWRITER_H
#define PI_ASM_HEXADECIMALWRITER_H


#include "Writer.h"

class HexadecimalWriter : public Writer{
private:
    uint8_t hexDigit(uint8_t);
public:

    void pushBack(uint8_t byte) override;

};


#endif //PI_ASM_HEXADECIMALWRITER_H
