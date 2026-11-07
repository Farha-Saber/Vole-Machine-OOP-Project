#ifndef MACHINE_H
#define MACHINE_H

#include <string>

#include "Memory.h"
#include "Screen.h"
#include "MemoryBus.h"
#include "RegisterFile.h"
#include "CPU.h"

class Machine {
private:
    Memory memory;
    Screen screen;
    MemoryBus bus;
    RegisterFile registers;
    CPU cpu;

public:
    Machine();

    void reset();

    bool loadProgram(
        const std::string& filePath,
        int startAddress
    );

    void run();

    bool step();

    Memory& getMemory();
    Screen& getScreen();
    RegisterFile& getRegisters();
    CPU& getCpu();
};

#endif