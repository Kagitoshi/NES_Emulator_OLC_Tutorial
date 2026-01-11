#ifndef NES_EMULATOR_BUS_H
#define NES_EMULATOR_BUS_H
#include <array>
#include <cstdint>

#include "olc6502.h"
#include "olc2C02.h"
#include "Cartridge.h"

class Bus
{

public:
    Bus();
    ~Bus();

public: //Devices on the bus
    olc6502 cpu;

    // The 2C02 Picture Processing Unit
    olc2C02 ppu;

    // Fake RAM for this part of the series (As of this writing, I am on Part2)
    std::array<uint8_t, 2048> cpuRam;

    // The Cartridge or "GamePak"
    std::shared_ptr<Cartridge> cart;

public: // Bus Read & Write
    void cpuWrite(uint16_t addr, uint8_t data);
    uint8_t cpuRead(uint16_t addr, bool bReadyOnly = false);

public: // System Interface
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void reset();
    void clock();

private:
    // A count of how many clocks have passed
    uint32_t nSystemClockCounter = 0;
};


#endif //NES_EMULATOR_BUS_H
