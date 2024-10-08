//
// Created by player402 on 24.09.24.
//

#ifndef PI_VM_MEMORY_H
#define PI_VM_MEMORY_H


#include <cstdint>
#include <stdexcept>
#include <cstdlib>

//Class representing computer RAM memory - template should be uint8, uint16, uint32 etc - depending on memory size
class Memory {
private:
    uint8_t* memory;

    int size;

public:
    void store(int address, uint8_t data)
    {
        if(address<0 || address>=size)
        {
            throw std::invalid_argument( "Memory: [writing] Address must be greater or equal to zero and less than memory size. Address given: "+std::to_string((int)address) );
        }
        memory[address] = data;
    }

    uint8_t load(int address)
    {
        if(address<0 || address>=size)
        {
            throw std::invalid_argument( "Memory: [reading] Address must be greater or equal to zero and less than memory size. Address given: "+std::to_string((int)address) );
        }
        return memory[address];
    }

    explicit Memory(int size)
    {
        this->size = size;
        memory = (uint8_t*)malloc(sizeof (uint8_t)*size);
    }

    ~Memory()
    {
        free(memory);
    }
};


#endif //PI_VM_MEMORY_H
