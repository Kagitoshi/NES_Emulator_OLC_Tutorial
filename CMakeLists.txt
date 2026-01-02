cmake_minimum_required(VERSION 3.26)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(NES_Emulator main.cpp
        Bus.cpp
        Bus.h
        olc6502.cpp
        olc6502.h
        olcPixelGameEngine.h
)
