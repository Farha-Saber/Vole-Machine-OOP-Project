#include "ProgramLoader.h"
#include "InstructionValidator.h"

#include <fstream>
#include <string>
#include <cctype>

bool ProgramLoader::isHexString(const std::string& text) {
    if (text.size() != 4) {
        return false;
    }

    for (char c : text) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}

bool ProgramLoader::readProgram(
    const std::string& filePath,
    std::vector<uint16_t>& instructions
) {
    instructions.clear();

    std::ifstream file(filePath);

    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        size_t first = line.find_first_not_of(" \t\r\n");

        if (first == std::string::npos || line[first] == ';') {
            continue;
        }

        std::string word = line.substr(first, 4);

        if (!isHexString(word)) {
            return false;
        }

        unsigned long value = std::stoul(word, nullptr, 16);

        InstructionFields fields{
            static_cast<uint8_t>((value >> 12) & 0xF),
            static_cast<uint8_t>((value >> 8) & 0xF),
            static_cast<uint8_t>((value >> 4) & 0xF),
            static_cast<uint8_t>(value & 0xF)
        };

        if (!InstructionValidator::validate(fields)) {
            return false;
        }

        instructions.push_back(
            static_cast<uint16_t>(value)
        );
    }

    return !instructions.empty();
}