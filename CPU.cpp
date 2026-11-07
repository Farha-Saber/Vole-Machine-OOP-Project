#include "CPU.h"
#include "InstructionValidator.h"

#include <iostream>
#include <sstream>
#include <iomanip>

CPU::CPU(MemoryBus& memoryBus, RegisterFile& registerFile)
    : programCounter(0),
      isHalted(false),
      bus(memoryBus),
      registers(registerFile) {
}

void CPU::reset() {
    programCounter = 0;
    isHalted = false;
    currentIR.clear();
}

bool CPU::fetch() {
    if (isHalted || programCounter < 0 ||
        programCounter > 0xFE) {
        isHalted = true;
        return false;
    }

    uint8_t byte1 = bus.readMemory(programCounter);
    uint8_t byte2 = bus.readMemory(programCounter + 1);

    std::stringstream ss;

    ss << std::uppercase
       << std::hex
       << std::setw(2) << std::setfill('0')
       << static_cast<int>(byte1)
       << std::setw(2) << std::setfill('0')
       << static_cast<int>(byte2);

    if (!currentIR.decode(ss.str())) {
        isHalted = true;
        return false;
    }

    programCounter += 2;

    return true;
}

bool CPU::decodeAndExecute() {
    if (isHalted || !currentIR.isValid()) {
        isHalted = true;
        return false;
    }

    char op = currentIR.getOpcode();

    int r = currentIR.getR();
    int s = currentIR.getS();
    int t = currentIR.getT();

    int xy = currentIR.getAddressXY();

    InstructionFields fields{
        static_cast<uint8_t>(
            op >= 'A' ? op - 'A' + 10 : op - '0'
        ),
        static_cast<uint8_t>(r),
        static_cast<uint8_t>(s),
        static_cast<uint8_t>(t)
    };

    if (!InstructionValidator::validate(fields)) {
        std::cout << "Invalid instruction: "
                  << currentIR.getRaw() << '\n';

        isHalted = true;
        return false;
    }

    switch (op) {

        case '1':
            registers.setRegister(
                r,
                bus.readMemory(xy)
            );
            break;

        case '2':
            registers.setRegister(
                r,
                static_cast<uint8_t>(xy)
            );
            break;

        case '3':
            bus.writeMemory(
                xy,
                registers.getRegister(r)
            );
            break;

        case '4':
            registers.setRegister(
                t,
                registers.getRegister(s)
            );
            break;

        case '5':
            registers.setRegister(
                r,
                alu.add(
                    registers.getRegister(s),
                    registers.getRegister(t)
                )
            );
            break;

        case '6':
            registers.setRegister(
                r,
                alu.addFloat(
                    registers.getRegister(s),
                    registers.getRegister(t)
                )
            );
            break;

        case '7':
            registers.setRegister(
                r,
                alu.bitwiseOR(
                    registers.getRegister(s),
                    registers.getRegister(t)
                )
            );
            break;

        case '8':
            registers.setRegister(
                r,
                alu.bitwiseAND(
                    registers.getRegister(s),
                    registers.getRegister(t)
                )
            );
            break;

        case '9':
            registers.setRegister(
                r,
                alu.bitwiseXOR(
                    registers.getRegister(s),
                    registers.getRegister(t)
                )
            );
            break;

        case 'A':
            // Rotate register R right by X positions.
            registers.setRegister(
                r,
                alu.rotateRight(
                    registers.getRegister(r),
                    t
                )
            );
            break;

        case 'B':
            if (alu.checkJump(
                registers.getRegister(r),
                registers.getRegister(0)
            )) {
                programCounter = xy;
            }
            break;

        case 'C':
            isHalted = true;
            break;

        default:
            std::cout << "Unknown opcode: " << op << '\n';
            isHalted = true;
            break;
    }

    return !isHalted;
}

bool CPU::step() {
    if (isHalted) {
        return false;
    }

    if (!fetch()) {
        return false;
    }

    return decodeAndExecute();
}

void CPU::run() {
    while (!isHalted) {
        if (!step()) {
            break;
        }
    }
}

int CPU::getPC() const {
    return programCounter;
}

void CPU::setPC(int address) {
    if (address >= 0 && address <= 0xFE &&
        address % 2 == 0) {
        programCounter = address;
    }
}

std::string CPU::getIRRaw() const {
    return currentIR.getRaw();
}

bool CPU::isExecutionHalted() const {
    return isHalted;
}