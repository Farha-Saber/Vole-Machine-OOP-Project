#ifndef INSTRUCTIONVALIDATOR_H
#define INSTRUCTIONVALIDATOR_H
#include <string>
#include <cstdint>  


struct InstructionFields {
    uint8_t opcode;
    uint8_t r;
    uint8_t x;
    uint8_t y;
    
};

class InstructionValidator {
public:
    static bool isValidOpcode(uint8_t opcode);
    static bool validateOperand(const InstructionFields& fields);
    static bool validate(const InstructionFields& fields);
};


#endif 