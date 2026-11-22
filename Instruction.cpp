#include "Instruction.h"
#include <cctype>
#include <sstream>

Instruction::Instruction() {
    clear();
}

Instruction::Instruction(const std::string& hexCode) {
    decode(hexCode);
}

bool Instruction::decode(const std::string& hexCode) {
    if (hexCode.length() != 4) {
        clear();
        return false;
    }

    
    for (char c : hexCode) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) {
            clear();
            return false;
        }
    }

    rawInstruction = hexCode;
    opcode = std::toupper(hexCode[0]);

    
    std::stringstream ssR, ssS, ssT, ssXY;
    
    ssR << std::hex << hexCode[1];
    ssR >> regR;

    ssS << std::hex << hexCode[2];
    ssS >> regS;

    ssT << std::hex << hexCode[3];
    ssT >> regT;

    ssXY << std::hex << hexCode.substr(2, 2);
    ssXY >> addressXY;

    return true;
}



void Instruction::clear() {
    rawInstruction = "0000";
    opcode = '0';
    regR = 0;
    regS = 0;
    regT = 0;
    addressXY = 0;
}


std::string Instruction::getRaw() const {
    return rawInstruction;
}


char Instruction::getOpcode() const {
    return opcode;
}


int Instruction::getR() const {
    return regR;
}


int Instruction::getS() const {
    return regS;
}


int Instruction::getT() const {
    return regT;
}


int Instruction::getAddressXY() const {
    return addressXY;
}


bool Instruction::isValid() const {
    return rawInstruction != "0000" || opcode == 'C';
}
