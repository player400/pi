#include <iostream>
#include "computer/Memory.h"
#include "computer/Processor.h"

int main() {

    Memory<uint8_t> mem(12);
    Processor<uint8_t> cpu(2, mem, 4);

    cpu.setRegister(Processor<uint8_t>::ALPHA, 0);
    cpu.setRegister(Processor<uint8_t>::BETA, 1);

    mem.store(10, 4);

    //HALD FLAG = 1;
    mem.store(0, 0b1001);
    mem.store(1, 0);

    //MOV 1111 < ACC
    mem.store(2, 0b0111);
    mem.store(3, 0b1111);

    //MOV ALPHA < BETA
    mem.store(4, 0b0001);
    mem.store(5, 0b0010);

    //MOV BETA < ACC
    mem.store(6, 0b0010);
    mem.store(7, 0b1111);

    //MOV PC < 1110

    mem.store(8, 0b0000);
    mem.store(9, 0b1110);

    while(true)
    {
        cpu.cycle();
    }

    return 0;
}
