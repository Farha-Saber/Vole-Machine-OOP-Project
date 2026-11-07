#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <cstdint>
#include <stdexcept>

class Memory {
private:
    std::array<uint8_t, 256> cells{};

public:
    Memory() {
        clear();
    }

    void clear() {
        cells.fill(0);
    }

    uint8_t read(int address) const {
        if (address < 0 || address > 0xFF) {
            throw std::out_of_range("Invalid memory address");
        }

        return cells[address];
    }

    void write(int address, uint8_t value) {
        if (address < 0 || address > 0xFF) {
            throw std::out_of_range("Invalid memory address");
        }

        cells[address] = value;
    }
};

#endif
