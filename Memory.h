#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>

using namespace std;

class Memory {
private:
    vector<string> storageLocations;

public:
    Memory() {
        storageLocations.resize(256, "0000");
    }

    string fetchValue(int address) {
        return storageLocations[address];
    }

    void storeValue(int address, string value) {
        storageLocations[address] = value;
    }
};

#endif
