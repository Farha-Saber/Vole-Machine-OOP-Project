#include "Register.h"

RegisterFile::RegisterFile() {
    registers.resize(16, "0000");
}

string RegisterFile::getRegister(int index) {
    return registers[index];
}

void RegisterFile::setRegister(int index, string value) {
    registers[index] = value;
}
