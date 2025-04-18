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
        Tokens/tokenizer.h
        Tokens/tokenizer.cpp
        Tokens/Variable.cpp
        Tokens/Variable.h
        Tokens/preprocessor.h
        Tokens/preprocessor.cpp
        Assembly/Entity.cpp
        Assembly/Entity.h
        Assembly/Assembly.cpp
        Assembly/Assembly.h
        Assembly/AssemblyInstruction.cpp
        Assembly/AssemblyInstruction.h
        Assembly/InstructionMOV.cpp
        Assembly/InstructionMOV.h
        Assembly/InstructionFLAG.cpp
        Assembly/InstructionFLAG.h
        Assembly/Data.cpp
        Assembly/Data.h
        Assembly/Writer/Writer.cpp
        Assembly/Writer/Writer.h
        Assembly/Writer/BinaryWriter.cpp
        Assembly/Writer/BinaryWriter.h
        ProgramArgumentProcessing.h
        Assembly/Writer/DecimalWriter.cpp
        Assembly/Writer/DecimalWriter.h
        Assembly/Writer/HexadecimalWriter.cpp
        Assembly/Writer/HexadecimalWriter.h
)
