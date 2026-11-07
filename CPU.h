#ifndef CPU_H
#define CPU_H

#include <string>
#include <cstdint>

#include "Instruction.h"
#include "MemoryBus.h"
#include "RegisterFile.h"
#include "ALU.h"

class CPU {
private:
    int programCounter;

    Instruction currentIR;

    bool isHalted;

    MemoryBus& bus;
    RegisterFile& registers;

    ALU alu;

public:
    CPU(MemoryBus& memoryBus, RegisterFile& registerFile);

    void reset();

    bool fetch();

    bool decodeAndExecute();

    bool step();

    void run();

    int getPC() const;

    void setPC(int address);

    std::string getIRRaw() const;

    bool isExecutionHalted() const;
};

#endif