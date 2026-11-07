#include "MemoryBus.h"

MemoryBus::MemoryBus(Memory& mem, Screen& scr)
    : memory(mem), screen(scr) {
}

uint8_t MemoryBus::readMemory(int address) const {
    return memory.read(address);
}

void MemoryBus::writeMemory(int address, uint8_t data) {
    memory.write(address, data);

    if (address == 0xFF) {
        screen.displayOutput(data);
    }
}