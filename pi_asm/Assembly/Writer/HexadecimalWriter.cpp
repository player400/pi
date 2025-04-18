//
// Created by player402 on 18.04.25.
//

#include "HexadecimalWriter.h"

void HexadecimalWriter::pushBack(uint8_t byte) {
    bytes.push_back(hexDigit(byte>>4));
    bytes.push_back(hexDigit(byte));
    bytes.push_back((uint8_t)'\n');
}

uint8_t HexadecimalWriter::hexDigit(uint8_t halfByte) {
    char digits[] = "0123456789ABCDEF";
    return (uint8_t)digits[halfByte & 0b1111];
}
