//
// Created by player402 on 06.10.24.
//

#ifndef PI_VM_BINARYFILEREADER_H
#define PI_VM_BINARYFILEREADER_H


#include <string>
#include <stdexcept>
#include <fstream>
#include "ExecutableFileReader.h"

class BinaryFileReader : public ExecutableFileReader{
public:

    void read(std::string fileName) override
    {
        reset();
        std::fstream file;
        file.open(fileName, std::fstream::in | std::ios::binary);
        if(!file.good())
        {
            throw std::invalid_argument("Binary File Reader: [file reading] Could not open the file '"+fileName+"'. Check the spelling. Remember to use either absolute paths or paths relative to this file.");
        }

        file.seekg(0, std::ios_base::end);
        long length = file.tellg();
        file.seekg(0, std::ios_base::beg);

        auto* tempArray = (uint8_t*)malloc(sizeof(uint8_t)*length);
        file.read((char*)tempArray, length);
        architectureBitWidth = tempArray[0];
        bytes.clear();
        for(int i=1;i<length;i++)
        {
            bytes.push_back(tempArray[i]);
        }
        free(tempArray);

        file.close();
    }
};


#endif //PI_VM_BINARYFILEREADER_H
