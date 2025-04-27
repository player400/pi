//
// Created by player402 on 02.10.24.
//

#ifndef PI_VM_CONTROLLERINTERFACE_H
#define PI_VM_CONTROLLERINTERFACE_H


#include <iostream>
#include "computer/Computer.h"
#include <iostream>

class ControllerInterface {
private:
    Computer& microcontroller;

    void displayOutput(bool printOutput, bool cycles)
    {
        if(!printOutput)
        {
            std::cout << "Output: \t";
        }
        try
        {
            std::cout << std::dec<<microcontroller.output() << "\t";
            std::cout <<" 0x"<<std::hex<< microcontroller.output() << "\t";
            if((char)microcontroller.output() == '\n')
            {
                std::cout <<"'\\n'";
            }
            else if((char)microcontroller.output() == '\b')
            {
                std::cout <<"'\\b'";
            }
            else if((char)microcontroller.output() == '\r')
            {
                std::cout <<"'\\r'";
            }
            else
            {
                std::cout <<"'" <<(char)microcontroller.output()<<"'";
            }
            if(cycles)
            {
                std::cout << " \t | \t Instruction "<<std::dec<<microcontroller.getCycleCount()<<std::endl;
            }
            std::cout<<std::endl;
        }
        catch(std::exception& e)
        {
            throw std::invalid_argument("ControllerInterface: [printing output] Exception was thrown, while printing microcontroller output: "+std::string(e.what()));
        }
    }

public:
    void run(bool debug = false, bool printOutput = false, bool cycles = false)
    {
        while(true) {
            std::cout.flush();
            if(!printOutput && !debug)
            {
                system("clear");
                displayOutput(printOutput, cycles);
            }
            if(microcontroller.isStopped())
            {

                bool inputTaken = false;
                std::string input;
                if(!printOutput && !debug)
                {
                    system("clear");
                }
                while(true)
                {
                    if(!printOutput || !inputTaken)
                    {
                        displayOutput(printOutput, cycles);
                    }
                    if(!printOutput)
                    {
                        std::cout<<"Code execution STOPPED by an internal command. Enter a number and press enter to provide input. Type 'r' to resume execution. Type 'e' to stop the emulator."<<std::endl;
                    }
                    std::cin>>input;
                    inputTaken = true;
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
