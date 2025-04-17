//
// Created by player402 on 17.04.25.
//

#include "Writer.h"

void Writer::writeAll(std::ostream &outputStream) {
    for(unsigned char byte : bytes)
    {
        outputStream<<byte;
    }
}
