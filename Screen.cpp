#include "Screen.h"

Screen::Screen() {
    outputLog = "";
}

void Screen::displayOutput(uint8_t value) {
    std::cout << "[Screen Output]: "
              << static_cast<int>(value)
              << std::endl;

    outputLog += std::to_string(value) + "\n";
}

void Screen::clear() {
    outputLog.clear();
}

const std::string& Screen::getOutputLog() const {
    return outputLog;
}