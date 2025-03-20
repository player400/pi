//
// Created by player402 on 01.10.24.
//

#ifndef PI_VM_COMPUTERARCHITECTURE_H
#define PI_VM_COMPUTERARCHITECTURE_H

//This will be an abstract class, that different architectures (4-bit, 8-bit, 32-bit and so-on) will be inheriting from.
//Those classes provide methods such as ,,getMovSource" - ie. are be doing part of cpu's job in instruction decoding.
//Those classes are supposed to know, for example, on which bits is the flag number located in the FLAG instruction code, or whether op-code 0 means ,,MOV" or ,,FLAG".
//This design choice separates CPU mechanics from the op-codes and layout of specific byte-code commands.
class ComputerArchitecture {
public:

    virtual int getRegistryCount() = 0;

    virtual int getWordWidth() = 0;

    virtual int getMemoryAddressWidth() = 0;


    //Below methods take the entire instruction code and return/check specific argument (classes inheriting from this class are supposed to know which bits to look at)

    virtual bool isMoveOperation(uint64_t instruction) = 0;

    virtual bool isMoveDirectionReversed(uint64_t instruction) = 0;

    virtual int getMovDestination(uint64_t instruction) = 0;

    virtual int getMovSource(uint64_t instruction) = 0;

    virtual int getFlagFlagNumber(uint64_t instruction) = 0;

    virtual bool getFlagValue(uint64_t instruction) = 0;

    virtual bool isFlagNegated(uint64_t instruction) = 0;

    virtual bool isFlagCarryIncluded(uint64_t instruction) = 0;

    virtual bool isFlagRegisterIncluded(uint64_t instruction) = 0;

    virtual int getFlagSourceRegisterNumber(uint64_t instruction) = 0;

    virtual int getMemoryCellWidth()
    {
        return 8;
    }

    virtual LogicalOperation getFlagLogicalOperation(uint64_t instruction) = 0;


};


#endif //PI_VM_COMPUTERARCHITECTURE_H
