#include "Machine.h"
#include "ProgramLoader.h"

#include <vector>
#include <cstdint>

Machine::Machine()
    : bus(memory, screen),
      cpu(bus, registers) {
    reset();
}

void Machine::reset() {
    memory.clear();
    screen.clear();
    registers.clear();
    cpu.reset();
}

bool Machine::loadProgram(
    const std::string& filePath,
    int startAddress
) {
    if (startAddress < 0 ||
        startAddress > 0xFE ||
        startAddress % 2 != 0) {
        return false;
    }

    std::vector<uint16_t> instructions;

    if (!ProgramLoader::readProgram(filePath, instructions)) {
        return false;
    }

    if (instructions.size() > (256 - startAddress) / 2) {
        return false;
    }

    reset();

    int address = startAddress;

    for (uint16_t instruction : instructions) {
        uint8_t highByte =
            static_cast<uint8_t>((instruction >> 8) & 0xFF);

        uint8_t lowByte =
            static_cast<uint8_t>(instruction & 0xFF);

        memory.write(address, highByte);
        memory.write(address + 1, lowByte);

        address += 2;
    }

    cpu.setPC(startAddress);

    return true;
}

void Machine::run() {
    cpu.run();
}

bool Machine::step() {
    return cpu.step();
}

Memory& Machine::getMemory() {
    return memory;
}

Screen& Machine::getScreen() {
    return screen;
}

RegisterFile& Machine::getRegisters() {
    return registers;
}

CPU& Machine::getCpu() {
    return cpu;
}