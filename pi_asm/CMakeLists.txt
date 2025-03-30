cmake_minimum_required(VERSION 3.27)
project(pi_asm)

set(CMAKE_CXX_STANDARD 23)

add_executable(pi_asm main.cpp
        Tokens/Pattern.cpp
        Tokens/Pattern.h
        Tokens/Instruction.cpp
        Tokens/Instruction.h
        Tokens/Hook.cpp
        Tokens/Hook.h
        Tokens/Comment.cpp
        Tokens/Comment.h
        Tokens/MOV.cpp
        Tokens/MOV.h
        Tokens/FLAG.cpp
        Tokens/FLAG.h
        Tokens/Value.cpp
        Tokens/Value.h
        Tokens/Program.cpp
        Tokens/Program.h
        Tokens/Expression.cpp
        Tokens/Expression.h
        Tokens/tokens.h
        Tokens/tokens.cpp
        Tokens/Logic.cpp
        Tokens/Logic.h
)
