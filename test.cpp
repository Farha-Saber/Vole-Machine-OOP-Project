#include <iostream>
#include "InstructionValidator.h"
using namespace std;

int main() {
    Instructionfields a = {4, 1, 2, 3};    // 4123
    Instructionfields b = {4, 0, 2, 3};    // 4023
    Instructionfields c = {12, 1, 2, 3};   // C123
    Instructionfields d = {12, 0, 0, 0};   // C000
    Instructionfields e = {15, 0, 0, 0};   // F000

    cout << InstructionValidator::validate(a) << endl;  // المفروض 0
    cout << InstructionValidator::validate(b) << endl;  // المفروض 1
    cout << InstructionValidator::validate(c) << endl;  // المفروض 0
    cout << InstructionValidator::validate(d) << endl;  // المفروض 1
    cout << InstructionValidator::validate(e) << endl;  // المفروض 0
} 