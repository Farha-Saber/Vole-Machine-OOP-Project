#ifndef ALU_H
#define ALU_H

using namespace std;

class ALU {
public:
     int add(int a, int b) {
        return a + b;
    }

    float addFloating(float a, float b) {
        return a + b;
    }

    int bitwiseOR(int a, int b) {
        return a | b;
    }

    int bitwiseAND(int a, int b) {
        return a & b;
    }

    int bitwiseXOR(int a, int b) {
        return a ^ b;
    }

    int rotateRight(int val, int shifts) {
        shifts %= 16;
        return (val >> shifts) | (val << (16 - shifts));
    }

    bool checkJump(int regVal, int regZeroVal) {
        return regVal == regZeroVal;
    }

    bool checkHalt(string op) {
        return op == "C";
    }
};

#endif
