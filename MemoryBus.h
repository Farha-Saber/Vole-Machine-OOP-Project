#ifndef MEMORYBUS_H
#define MEMORYBUS_H

#include <cstdint>
#include "Memory.h"
#include "Screen.h"

class MemoryBus {
private:
    Memory& memory;
    Screen& screen;

public:
    MemoryBus(Memory& mem, Screen& scr);

    uint8_t readMemory(int address) const;

    void writeMemory(int address, uint8_t data);
};

#endif