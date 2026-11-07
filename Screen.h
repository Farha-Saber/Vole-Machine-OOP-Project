#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdint>

class Screen {
private:
    std::string outputLog;  

public:
    Screen();
    
    void displayOutput(uint8_t value);
    
    void clear();
    
    const std::string& getOutputLog() const;
};

#endif 