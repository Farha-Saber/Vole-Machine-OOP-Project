#include "InstructionValidator.h"

bool InstructionValidator::isValidOpcode(uint8_t opcode) {
       if (opcode >= 0x1 && opcode <= 0xC) {
        return true;
    }
    return false;
}
bool InstructionValidator::validate(const InstructionFields& fields) {
    return isValidOpcode(fields.opcode) && validateOperand(fields);
}

bool InstructionValidator::validateOperand(const InstructionFields& fields) {

    switch (fields.opcode) {
        case 0x4: 
            return fields.r == 0;
        case 0xA: 
            return fields.x ==0;
        case 0xC: 
            return fields.y == 0 && fields.x == 0 && fields.r == 0;
        default:
            return true; 
    }
  
   }

