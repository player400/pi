//
// Created by player402 on 17.04.25.
//

#ifndef PI_ASM_WRITER_H
#define PI_ASM_WRITER_H


#include <vector>
#include <cstdint>
#include <ostream>

class Writer {
protected:
    std::vector<uint8_t> bytes;

public:
    virtual void pushBack(uint8_t byte) = 0;

    void writeAll(std::ostream &outputStream);
};


#endif //PI_ASM_WRITER_H
