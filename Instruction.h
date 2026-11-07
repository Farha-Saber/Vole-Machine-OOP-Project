#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

class Instruction {
private:
    std::string rawInstruction;

    char opcode;
    int regR;
    int regS;
    int regT;
    int addressXY;

public:
    Instruction();

    explicit Instruction(const std::string& hexCode);

    bool decode(const std::string& hexCode);

    void clear();

    std::string getRaw() const;
    char getOpcode() const;

    int getR() const;
    int getS() const;
    int getT() const;

    int getAddressXY() const;

    bool isValid() const;
};

#endif