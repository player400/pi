//
// Created by player402 on 02.10.24.
//

#ifndef PI_VM_BIT4_H
#define PI_VM_BIT4_H


#include "ComputerArchitecture.h"
#include "../../utils.h"

class Bit4 : public ComputerArchitecture{
private:
    const int wordWidth = 4;
    const int registryAddressSpaceByteCount = 2;
    int registryCount;

public:
    int getRegistryCount() override
    {
        return registryCount;
    }

    int getWordWidth() override
    {
        return wordWidth;
    }

    Bit4()
    {
        registryCount = powerOfTwo(registryAddressSpaceByteCount);
    }
};


#endif //PI_VM_BIT4_H
