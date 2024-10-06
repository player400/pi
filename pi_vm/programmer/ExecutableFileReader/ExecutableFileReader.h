//
// Created by player402 on 05.10.24.
//

#ifndef PI_VM_EXECUTABLEFILEREADER_H
#define PI_VM_EXECUTABLEFILEREADER_H




class ExecutableFileReader {
protected:
    int currentByte=0;
    int architectureBitWidth;
    std::vector<uint8_t>bytes;

public:
    virtual void read(std::string fileName) = 0;

    uint8_t nextByte()
    {
        return bytes[currentByte++];
    }

    bool isNextByte()
    {
        if(currentByte<bytes.size())
        {
            return true;
        }
        return false;
    }

    void reset()
    {
        currentByte=0;
    }

    int getArchitectureBitWidth() const {
        return architectureBitWidth;
    }

    int howManyBytes()
    {
        return bytes.size();
    }

};


#endif //PI_VM_EXECUTABLEFILEREADER_H
