#include <iostream>
#include "computer/Memory.h"

int main() {

    Memory<uint8_t> test(240);

    test.store(239, 7);
    std::cout << (int)test.load(239) << std::endl;
    test.load(240);
    return 0;
}
