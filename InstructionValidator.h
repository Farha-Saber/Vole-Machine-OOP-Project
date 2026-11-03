#ifndef INSTRUCTIONVALIDATOR_H
#define INSTRUCTIONVALIDATOR_H
#include <string>
#include <cstdint>  


struct Instructionfields {
    uint8_t opcode;
    uint8_t r;
    uint8_t x;
    uint8_t y;
    
};

class InstructionValidator {
public:
    static bool isValidOpcode(uint8_t opcode);
    static bool validateOperand(const Instructionfields& fields);
    static bool validate(const Instructionfields& fields);
};


#endif 