#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>

using namespace std;

class Memory {
private:
    vector<string> storageLocations;

public:
    Memory();
    string fetchValue(int address);
    void storeValue(int address, string value);
};

#endif
