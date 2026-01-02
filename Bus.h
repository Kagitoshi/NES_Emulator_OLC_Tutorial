#ifndef NES_EMULATOR_BUS_H
#define NES_EMULATOR_BUS_H
#include <array>
#include <cstdint>
#include "olc6502.h"

class Bus{

public:
    Bus();
    ~Bus();


public: //Devices on the bus
    olc6502 cpu;

    // Fake RAM for this part of the series (As of this writing, I am on Part2)
    std::array<uint8_t, 64 * 1024> ram;

public: // Bus Read & Write
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr, bool bReadyOnly = false);

};


#endif //NES_EMULATOR_BUS_H
