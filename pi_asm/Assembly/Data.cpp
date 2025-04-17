//
// Created by player402 on 17.04.25.
//

#include "Data.h"

Data::Data(Writer &writer, Architecture architecture, int times) : Entity(writer, architecture), times(times) {}

void Data::pushBack(uint8_t byte) {
    bytes.push_back(byte);
}

void Data::write() {
    for(int i=0;i<times;i++)
    {
        for(int j=0;j<bytes.size();j++)
        {
            writer.pushBack(bytes[j]);
        }
    }
}
