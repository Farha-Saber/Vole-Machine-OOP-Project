#ifndef ALU_H
#define ALU_H

#include <string>

using namespace std;

class ALU {
public:
    int add(int a, int b);
    float addFloating(float a, float b);
    int bitwiseOR(int a, int b);
    int bitwiseAND(int a, int b);
    int bitwiseXOR(int a, int b);
    int rotateRight(int val, int shifts);
    bool checkJump(int regVal, int regZeroVal);
    bool checkHalt(string op);
};

#endif
