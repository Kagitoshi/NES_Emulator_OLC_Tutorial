#include "Bus.h"


Bus::Bus()
{
    // Connect CPU to communication bus
    {
        cpu.ConnectBus(this);
    }

    //Clear RAM contents, 万が一。笑。
    for(auto& i : cpuRam)
    {
        i = 0x00;
    }
}

Bus::~Bus()
{
}

void Bus::cpuWrite(uint16_t addr, uint8_t data)
{
    if (cart->cpuWrite(addr, data))
    {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        cpuRam[addr & 0x07FF] = data; //07FF = 2047, or in other words 2048 bits or 2 kilobytes
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        ppu.cpuWrite(addr & 0x0007, data);
    }
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly)
{
    uint8_t data = 0x00;

    if (cart->cpuRead(addr, data))
    {

    }
    else if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        data = cpuRam[addr & 0x07FF]; //07FF = 2047, or in other words 2048 bits or 2 kilobytes
    }
    else if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        data = ppu.cpuRead(addr & 0x0007, bReadOnly);
    }


    return data;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge)
{
    this->cart = cartridge;
    ppu.ConnectCartridge(cartridge);
}

void Bus::reset()
{
    cpu.reset();
    nSystemClockCounter = 0;
}

void Bus::clock()
{
    ppu.clock();

    // The CPU clock runs three times slower than the ppu clock
    // So he uses the variable below to know when to increment the cpu clock cycle.
    if ((nSystemClockCounter % 3) == 0)
    {
        cpu.clock();
    }

    nSystemClockCounter++;
}
