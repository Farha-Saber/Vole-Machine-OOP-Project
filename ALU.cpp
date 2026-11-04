#include "ALU.h"

int ALU::add(int a, int b) {
    return a + b;
}

float ALU::addFloating(float a, float b) {
    return a + b;
}

int ALU::bitwiseOR(int a, int b) {
    return a | b;
}

int ALU::bitwiseAND(int a, int b) {
    return a & b;
}

int ALU::bitwiseXOR(int a, int b) {
    return a ^ b;
}

int ALU::rotateRight(int val, int shifts) {
    shifts %= 16;
    return (val >> shifts) | (val << (16 - shifts));
}

bool ALU::checkJump(int regVal, int regZeroVal) {
    return regVal == regZeroVal;
}

bool ALU::checkHalt(string op) {
    return op == "C";
}
