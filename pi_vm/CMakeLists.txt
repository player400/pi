cmake_minimum_required(VERSION 3.27)
project(pi_vm)

set(CMAKE_CXX_STANDARD 23)

add_executable(pi_vm main.cpp
        computer/Memory.h)
