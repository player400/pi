//
// Created by player402 on 02.10.24.
//

#ifndef PI_VM_CONTROLLERINTERFACE_H
#define PI_VM_CONTROLLERINTERFACE_H


#include <iostream>
#include "computer/Computer.h"

class ControllerInterface {
private:
    Computer& microcontroller;

public:
    void run()
    {
        while(true) {

            system("clear");
            std::cout << "Output: " << microcontroller.output() << std::endl;
            if(microcontroller.isStopped())
            {
                //For now input is required to resume a stopped processor - you can just type the same thing that's already in output, so that nothing wil change.
                std::string input;
                while(true)
                {
                    system("clear");
                    std::cout << "Output: " << microcontroller.output() << std::endl;
                    std::cout<<"Code execution STOPPED by an internal command. Enter a number and press enter to provide input. Type 'r' to resume execution."<<std::endl;
                    std::cin>>input;
                    if(input!="r")
                    {
                        microcontroller.input(stoi(input));
                    }
                    else
                    {
                        microcontroller.resume();
                        break;
                    }
                }
            }
        }
    }

    ControllerInterface(Computer& computer):microcontroller(computer)
    {

    }

};


#endif //PI_VM_CONTROLLERINTERFACE_H
