#ifndef NES_EMULATOR_OLC2C02_H
#define NES_EMULATOR_OLC2C02_H

#include <cstdint>
#include <memory>


#include "olcPixelGameEngine.h"
#include "Cartridge.h"

class olc2C02
{
public:
    olc2C02();
    ~olc2C02();

private:
    // VRAM that holds the name table information.
    // While it is 2KB, he is splitting it into two 1KB chunks.
    uint8_t tblName[2][1024];
    uint8_t tblPalette[32];

    // He is adding this to run his own mapper.
    // And as he notes this as "Javid Future" for a reminder
    uint8_t tblPattern[2][4096];

private:
    olc::Pixel palScreen[0x40];
    olc::Sprite sprScreen = olc::Sprite(256, 240);
    olc::Sprite sprNameTable[2] = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
    olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
    // Debugging Utilities
    olc::Sprite& GetScreen();
    olc::Sprite& GetNameTable(uint8_t i);
    olc::Sprite& GetPatternTable(uint8_t i, uint8_t palette);

    olc::Pixel& GetColourFromPaletteRam(uint8_t palette, uint8_t pixel);

    bool frame_complete = false;

private:
    uint16_t scanline = 0;
    uint16_t cycle = 0;

public:
    // Communication with the Main Bus. Connects the PPU to the CPU bus.
    uint8_t cpuRead(uint16_t addr, bool readOnly = false);
    void cpuWrite(uint16_t addr, uint8_t data);

    // Communication with the PPU Bus. Connects the PPU to its' own bus.
    uint8_t ppuRead(uint16_t addr, bool readOnly = false);
    void ppuWrite(uint16_t addr, uint8_t data);

private:
    // The Cartridge or "GamePak"
    std::shared_ptr<Cartridge> cart;

public:
    // Interface
    void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void clock();
};


#endif //NES_EMULATOR_OLC2C02_H