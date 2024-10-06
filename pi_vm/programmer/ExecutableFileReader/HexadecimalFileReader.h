//
// Created by player402 on 06.10.24.
//

#ifndef PI_VM_HEXADECIMALFILEREADER_H
#define PI_VM_HEXADECIMALFILEREADER_H


#include <string>
#include <stdexcept>
#include <fstream>
#include "ExecutableFileReader.h"

class HexadecimalFileReader : public ExecutableFileReader{
public:

    void read(std::string fileName) override
    {
        reset();
        std::fstream file;
        file.open(fileName, std::fstream::in);
        if(!file.good())
        {
            throw std::invalid_argument("Programmer: [file reading] Could not open the file '"+fileName+"'. Check the spelling. Remember to use either absolute paths or paths relative to this file.");
        }
        file >> std::hex >> architectureBitWidth;
        bytes.clear();
        while(!file.eof())
        {
            int byte;
            if(file >> std::hex >> byte) {
                bytes.push_back(byte);
            }
        }
        file.close();
    }

};


#endif //PI_VM_HEXADECIMALFILEREADER_H
