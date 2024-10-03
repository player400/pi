//
// Created by player402 on 01.10.24.
//

#ifndef PI_VM_COMPUTERARCHITECTURE_H
#define PI_VM_COMPUTERARCHITECTURE_H

//This will be an abstract class, that different architectures (4-bit, 8-bit, 32-bit and so-on) will be inheriting from.
//Those classes will provide methods such as ,,getMovOriginAddress" - ie. will be doing part of cpu's job in intruction decoding
//This design choice separates CPU mechanics from the op-codes and layout of specific byte-code commands.
class ComputerArchitecture {
public:

    virtual int getRegistryCount() = 0;

    virtual int getWordWidth() = 0;



};


#endif //PI_VM_COMPUTERARCHITECTURE_H
