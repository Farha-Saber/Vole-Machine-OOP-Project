#include "InstructionValidator.h"


bool InstructionValidator::isValidOpcode(uint8_t opcode) {
       if (opcode >= 1 && opcode <= 12) {
        return true;
    }
    return false;
}

bool InstructionValidator::validate(const Instructionfields& fields) {
    return isValidOpcode(fields.opcode) && validateOperand(fields);
}

   bool InstructionValidator::validateOperand(const Instructionfields& fields) {

    switch (fields.opcode) {
        case 4: 
            return fields.r == 0;
        case 10: 
            return fields.x ==0;
        case 12: 
            return fields.y == 0 && fields.x == 0 && fields.r == 0;
        default:
            return true; 
    }

   }