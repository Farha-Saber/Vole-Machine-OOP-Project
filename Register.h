
#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <array>
#include <cstdint>
#include <stdexcept>

class RegisterFile {
private:
    std::array<uint8_t, 16> registers{};

public:
    RegisterFile() {
        clear();
    }

    void clear() {
        registers.fill(0);
    }

    uint8_t getRegister(int index) const {
        if (index < 0 || index > 15) {
            throw std::out_of_range("Invalid register index");
        }

        return registers[index];
    }

    void setRegister(int index, uint8_t value) {
        if (index < 0 || index > 15) {
            throw std::out_of_range("Invalid register index");
        }

        registers[index] = value;
    }
};

#endif
