//
// Created by player402 on 18.04.25.
//

#include "DecimalWriter.h"

void DecimalWriter::pushBack(uint8_t byte) {
    std::string number = std::to_string((int)byte);
    for(char digit : number)
    {
        bytes.push_back((uint8_t)digit);
    }
    bytes.push_back((uint8_t)'\n');
}
