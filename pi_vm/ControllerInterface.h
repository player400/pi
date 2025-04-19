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
    void run(bool debug = false, bool printOutput = false)
    {
        while(true) {
            if(!printOutput && !debug)
            {
                try
                {
                    system("clear");
                    std::cout << "Output: " << std::dec<<microcontroller.output();
                    std::cout<<" 0x"<<std::hex<< microcontroller.output();
                    std::cout<<" " <<(char)microcontroller.output()<<std::endl;
                }
                catch(std::exception& e)
                {
                    throw std::invalid_argument("ControllerInterface: [printing output] Exception was thrown, while printing microcontroller output: "+std::string(e.what()));
                }
            }
            if(microcontroller.isStopped())
            {
                std::string input;
                if(!printOutput && !debug)
                {
                    system("clear");
                }
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
                    if(!printOutput)
                    {
                        std::cout<<"Code execution STOPPED by an internal command. Enter a number and press enter to provide input. Type 'r' to resume execution. Type 'e' to stop the emulator."<<std::endl;
                    }
                    std::cin>>input;
                    if(input!="r" && input != "e")
                    {
                        try
                        {
                            microcontroller.input(stoi(input));
                            if(!printOutput && !debug)
                            {
                                system("clear");
                            }
                        }
                        catch (std::exception& e)
                        {
                            throw std::invalid_argument("ControllerInterface: [taking input] The Computer threw an exception, while taking input (input must be a number): "+std::string(e.what()));
                        }
                    }
                    else if(input == "r")
                    {
                        microcontroller.resume();
                        if(!printOutput && !debug)
                        {
                            system("clear");
                        }
                        break;
                    }
                    else if(input == "e")
                    {
                        exit(1);
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
