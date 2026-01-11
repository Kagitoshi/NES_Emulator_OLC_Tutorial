cmake_minimum_required(VERSION 3.26)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(NES_Emulator main.cpp
        Bus.cpp
        Bus.h
        olc6502.h
        olc6502.cpp
        olcPixelGameEngine.h
        olc2C02.cpp
        olc2C02.h
        Cartridge.cpp
        Cartridge.h
        Mapper.cpp
        Mapper.h
        Mapper_000.cpp
        Mapper_000.h
)
