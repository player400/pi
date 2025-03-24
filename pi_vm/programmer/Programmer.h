//
// Created by player402 on 06.10.24.
//

#ifndef PI_VM_PROGRAMMER_H
#define PI_VM_PROGRAMMER_H

#include "../computer/Computer.h"
#include "ExecutableFileReader/BinaryFileReader.h"
#include "ExecutableFileReader/HexadecimalFileReader.h"
#include "ExecutableFileReader/DecimalFileReader.h"

class Programmer {

    ExecutableFileReader* reader = nullptr;

public:
    void program(std::string& fileName, Computer& unit)
    {
        try
        {
            reader->read(fileName);
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("Programmer: [file reading] Exception was thrown while reading the program file: "+ std::string(e.what()));
        }
        unit.programmingMode();
        int architectureWidth = reader->getArchitectureBitWidth();
        if(architectureWidth != unit.getArchitectureWidth())
        {
            throw std::invalid_argument("Programmer: [programming] You are trying to program a "+std::to_string(unit.getArchitectureWidth())+" bit machine with an executable for a "
            +std::to_string(architectureWidth)+" bit machine... Stop. Get some help. This is NOT supported.");
        }
        int bytesPerRegister = (architectureWidth-1)/BYTE_SIZE+1;
        for(int i=0;i<unit.getRegistryCount();i++)
        {
            uint64_t currentRegister = 0;
            for(int j=bytesPerRegister-1;j>=0;j--)
            {
                uint64_t byte = reader->nextByte();
                byte = byte<<(BYTE_SIZE*j);
                currentRegister = currentRegister|byte;
            }
            try
            {
                unit.program(i, currentRegister);
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("Programmer: [programming] Exception was thrown by the machine while programming registers: "+std::string(e.what()));
            }
        }
        uint64_t address = unit.getRegistryCount();
        while(reader->isNextByte())
        {
            try
            {
                unit.program(address++, reader->nextByte());
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("Programmer: [programming] Exception was thrown by the machine while programming memory: "+std::string(e.what()));
            }
        }
        unit.runningMode();
        reader->reset();
    }



    Programmer(ExecutableFileType fileType)
    {
        switch(fileType)
        {
            case BINARY: reader = new BinaryFileReader; break;
            case HEXADECIMAL: reader = new HexadecimalFileReader; break;
            case DECIMAL: reader = new DecimalFileReader; break;
            default: throw std::invalid_argument("Programmer: [setup] File type set to none.");
        }
    }

    ~Programmer()
    {
        if(reader!= nullptr)
        {
            delete reader;
        }
    }


};


#endif //PI_VM_PROGRAMMER_H
