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
                std::string input;
                system("clear");
                while(true)
                {
                    std::cout << "Output: " << (char)microcontroller.output() << std::endl;
                    std::cout<<"Code execution STOPPED by an internal command. Enter a number and press enter to provide input. Type 'r' to resume execution."<<std::endl;
                    std::cin>>input;
                    if(input!="r")
                    {
                        try
                        {
                            microcontroller.input(stoi(input));
                            system("clear");
                        }
                        catch (std::invalid_argument& exception)
                        {
                            std::cerr<<"NON-FATAL User Command Line Interface: [parsing input] Input should be an integer or 'r'. Input given: '"+input+"'."<<std::endl;
                        }
                    }
                    else
                    {
                        microcontroller.resume();
                        system("clear");
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
