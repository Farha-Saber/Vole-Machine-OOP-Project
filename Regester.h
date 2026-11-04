#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <vector>
#include <string>

using namespace std;

class RegisterFile {
private:
    vector<string> registers;

public:
    RegisterFile() {
        registers.resize(16, "0000");
    }

    string getRegister(int index) {
        return registers[index];
    }

    void setRegister(int index, string value) {
        registers[index] = value;
    }
};

#endif
