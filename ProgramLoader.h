#ifndef PROGRAMLOADER_H
#define PROGRAMLOADER_H

#include <string>
#include <vector>
#include <cstdint>

class ProgramLoader {
public:
    static bool isHexString(const std::string& text);
    static bool readProgram(const std::string& filepath, std::vector<uint16_t>& instructions);
};


#endif