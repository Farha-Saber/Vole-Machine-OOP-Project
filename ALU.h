#ifndef ALU_H
#define ALU_H

#include <cstdint>
#include <cmath>

class ALU {
public:
    uint8_t add(uint8_t a, uint8_t b) {
        return static_cast<uint8_t>(a + b);
    }

    uint8_t bitwiseOR(uint8_t a, uint8_t b) {
        return a | b;
    }

    uint8_t bitwiseAND(uint8_t a, uint8_t b) {
        return a & b;
    }

    uint8_t bitwiseXOR(uint8_t a, uint8_t b) {
        return a ^ b;
    }

    uint8_t rotateRight(uint8_t value, int shifts) {
        shifts %= 8;

        if (shifts == 0) {
            return value;
        }

        return static_cast<uint8_t>(
            (value >> shifts) |
            (value << (8 - shifts))
        );
    }

    bool checkJump(uint8_t regValue, uint8_t zeroValue) {
        return regValue == zeroValue;
    }

    double decodeFloat(uint8_t v) const {
        int sign = (v >> 7) & 1;
        int exponent = (v >> 4) & 0x7;
        int mantissa = v & 0xF;

        double value = (static_cast<double>(mantissa) / 16.0) * std::pow(2.0, exponent - 4);
        if (sign) {
            value = -value;
        }
        return value;
    }

    uint8_t encodeFloat(double val) const {
        if (std::abs(val) < 1e-7) {
            return 0x00;
        }

        uint8_t sign = 0;
        if (val < 0) {
            sign = 1;
            val = -val;
        }

        int exponent = 4; 
        while (val >= 1.0) {
            val /= 2.0;
            exponent++;
        }
        while (val < 0.5 && val > 0.0) {
            val *= 2.0;
            exponent--;
        }

        if (exponent < 0) {
            return 0x00; 
        }

        if (exponent > 7) {
            return static_cast<uint8_t>((sign << 7) | (0x7 << 4) | 0xF);
        }

        int mantissa = static_cast<int>(val * 16.0);
        if (mantissa > 15) mantissa = 15;

        return static_cast<uint8_t>((sign << 7) | (exponent << 4) | (mantissa & 0xF));
    }

    uint8_t addFloat(uint8_t a, uint8_t b) {
        double da = decodeFloat(a);
        double db = decodeFloat(b);
        double sum = da + db;
        return encodeFloat(sum);
    }
};

#endif
