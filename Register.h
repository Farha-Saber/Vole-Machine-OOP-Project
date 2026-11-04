#ifndef REGISTERFILE_H
#define REGISTERFILE_H

#include <vector>
#include <string>

using namespace std;

class RegisterFile {
private:
    vector<string> registers;

public:
    RegisterFile();
    string getRegister(int index);
    void setRegister(int index, string value);
};

#endif
