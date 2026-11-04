//Date: 6 Oct 1973
// مره واحد راح يقعد على القهوه اتلسع


#include "InstructionValidator.h"


bool InstructionValidator::isValidOpcode(uint8_t opcode) {
       if (opcode >= 1 && opcode <= 12) {
        return true;
    }
    return false;
}
// /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*
bool InstructionValidator::validate(const InstructionFields& fields) {
    return isValidOpcode(fields.opcode) && validateOperand(fields);
}
// /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*

   bool InstructionValidator::validateOperand(const InstructionFields& fields) {

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
   // /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/
