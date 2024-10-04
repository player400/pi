//
// Created by player402 on 25.09.24.
//

#ifndef PI_VM_UTILS_H
#define PI_VM_UTILS_H

int powerOfTwo(int exponent)
{
    int result=1;
    for(int i=0; i<exponent;i++)
    {
        result*=2;
    }
    return result;
}

enum LogicalOperation
{
    ADD,
    MULTIPLY
};

#endif //PI_VM_UTILS_H
