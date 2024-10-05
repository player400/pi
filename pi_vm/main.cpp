#include <iostream>


#define BAD_ARGUMENTS_EXIT 5

#include "computer/Memory.h"
#include "computer/Processor.h"
#include "computer/Computer.h"
#include "ControllerInterface.h"
#include "ProgramArgumentParser.h"
#include <thread>




int main(int argc, char* argv[]) {

    std::vector<ParsedOption>options;
    parseProgramArguments(argc,argv, options);


    Computer unit;


    unit.programmingMode();
    unit.program(0, 4);
    unit.program(1, 0);
    unit.program(2, 1);
    unit.program(3, 0);
    unit.program(4, 0b1001);
    unit.program(5, 0);
    unit.program(6, 0b0111);
    unit.program(7, 0b1111);
    unit.program(8, 0b0001);
    unit.program(9, 0b0010);
    unit.program(10, 0b0010);
    unit.program(11, 0b1111);
    unit.program(12, 0b0000);
    unit.program(13, 0b1110);
    unit.program(14, 4);
    unit.runningMode();

    ControllerInterface interface(unit);

    std::thread t1([&interface](){interface.run();});

    while(true)
    {
        unit.cycle();
    }

    return 0;
}
