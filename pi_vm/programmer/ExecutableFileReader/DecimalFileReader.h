//
// Created by player402 on 05.10.24.
//

#ifndef PI_VM_DECIMALFILEREADER_H
#define PI_VM_DECIMALFILEREADER_H


#include <string>
#include "ExecutableFileReader.h"
#include "fstream"

class DecimalFileReader : public ExecutableFileReader{
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
        file>>architectureBitWidth;
        bytes.clear();
        while(!file.eof())
        {
            int byte;
            if(file >> byte) {
                bytes.push_back(byte);
            }
        }
        file.close();
    }
};


#endif //PI_VM_DECIMALFILEREADER_H
