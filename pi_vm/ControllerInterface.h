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
            try
            {
                std::cout << "Output: " << microcontroller.output() << std::endl;
            }
            catch(std::exception& e)
            {
                throw std::invalid_argument("ControllerInterface: [printing output] Exception was thrown, while printing microcontroller output: "+std::string(e.what()));
            }
            if(microcontroller.isStopped())
            {
                std::string input;
                system("clear");
                while(true)
                {
                    try
                    {
                        std::cout << "Output: " << std::dec<<microcontroller.output();
                        std::cout<<" 0x"<<std::hex<< microcontroller.output();
                        std::cout<<" " <<(char)microcontroller.output()<<std::endl;
                    }
                    catch(std::exception& e)
                    {
                        throw std::invalid_argument("ControllerInterface: [printing output] Exception was thrown, while printing microcontroller output: "+std::string(e.what()));
                    }
                    std::cout<<"Code execution STOPPED by an internal command. Enter a number and press enter to provide input. Type 'r' to resume execution."<<std::endl;
                    std::cin>>input;
                    if(input!="r")
                    {
                        try
                        {
                            microcontroller.input(stoi(input));
                            system("clear");
                        }
                        catch (std::exception& e)
                        {
                            throw std::invalid_argument("ControllerInterface: [taking input] The Computer threw an exception, while taking input: "+std::string(e.what()));
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
