
#include "computer/Computer.h"
#include "ControllerInterface.h"
#include "ProgramArgumentProcessing.h"
#include "programmer/Programmer.h"
#include <thread>





int main(int argc, char* argv[]) {
    ExecutableFileType fileType;
    std::string fileName;
    bool displayHelp;
    bool displayVersion;

    applyProgramArguments(displayHelp, displayVersion, fileType, fileName, argc, argv);

    Computer unit;

    Programmer programmer(fileType);

    programmer.program(fileName, unit);

    ControllerInterface interface(unit);

    std::thread t1([&interface](){interface.run();});

    while(true)
    {
        unit.cycle();
    }
}
