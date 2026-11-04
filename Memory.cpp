#include "Memory.h"

Memory::Memory() {
    storageLocations.resize(256, "0000");
}

string Memory::fetchValue(int address) {
    return storageLocations[address];
}

void Memory::storeValue(int address, string value) {
    storageLocations[address] = value;
}
