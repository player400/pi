cmake_minimum_required(VERSION 3.27)
project(pi_vm)

set(CMAKE_CXX_STANDARD 23)

add_executable(pi_vm main.cpp
        computer/Memory.h
        computer/Processor.h
        utils.h
        computer/Computer.h
        computer/architecture/ComputerArchitecture.h
        ControllerInterface.h
        computer/architecture/Bit4.h
        ProgramArgumentProcessing.h
        programmer/ExecutableFileReader/ExecutableFileReader.h
        programmer/ExecutableFileReader/DecimalFileReader.h
        programmer/ExecutableFileReader/HexadecimalFileReader.h
        programmer/ExecutableFileReader/BinaryFileReader.h
        programmer/Programmer.h
        computer/architecture/Bit8.h)
