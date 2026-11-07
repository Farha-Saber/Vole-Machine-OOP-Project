#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdint>
#include "Machine.h"

using namespace std;

void displayMachineState(Machine& machine) {
    cout << "\n========== MACHINE STATE ==========\n";

    cout << hex << uppercase << setfill('0');

    cout << "Program Counter (PC): "
         << setw(2) << static_cast<int>(machine.getCpu().getPC())
         << "\n";

    cout << "Instruction Register (IR): "
         << setw(4) << machine.getCpu().getIRRaw()
         << "\n";

    cout << "\n========== REGISTERS ==========\n";

    for (int i = 0; i < 16; i++) {
        cout << "R" << hex << i << ": "
             << setw(2)
             << static_cast<int>(machine.getRegisters().getRegister(i))
             << "    ";

        if ((i + 1) % 4 == 0)
            cout << "\n";
    }

    cout << "\n========== MEMORY ==========\n";

    for (int i = 0; i < 256; i++) {
        if (i % 16 == 0) {
            cout << "\n"
                 << setw(2) << i << " | ";
        }

        cout << setw(2)
             << static_cast<int>(machine.getMemory().read(i))
             << " ";
    }

    cout << dec << setfill(' ') << "\n";

    // عرض سجل مخرجات الشاشة
    cout << "\n========== SCREEN OUTPUT LOG ==========\n";
    cout << machine.getScreen().getOutputLog();
    if (machine.getScreen().getOutputLog().empty()) {
        cout << "(No output yet)\n";
    }
    cout << "=======================================\n";
}

void showMenu() {
    cout << "\n========== VOLE MACHINE SIMULATOR ==========\n";
    cout << "1. Load Program\n";
    cout << "2. Run Program\n";
    cout << "3. Execute One Step\n";
    cout << "4. Display Machine State\n";
    cout << "5. Edit Register\n";
    cout << "6. Edit Memory Cell\n";
    cout << "7. Reset Machine\n";
    cout << "8. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Machine machine;

    bool programLoaded = false;

    int choice;

    do {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

        case 1: {
            string filePath;
            int startAddress;

            cout << "Enter program file path: ";
            cin >> filePath;

            cout << "Enter starting address (hexadecimal): ";
            cin >> hex >> startAddress >> dec;

            programLoaded = machine.loadProgram(filePath, startAddress);

            if (programLoaded) {
                cout << "Program loaded successfully!\n";
            }
            else {
                cout << "Failed to load program.\n";
            }

            break;
        }

        case 2: {
            if (!programLoaded) {
                cout << "Please load a program first.\n";
                break;
            }

            cout << "Running program...\n";
            machine.run();
            displayMachineState(machine);

            break;
        }

        case 3: {
            if (!programLoaded) {
                cout << "Please load a program first.\n";
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Starting step-by-step execution.\n";
            cout << "Press Enter for the next step (or type 'q' then Enter to return to menu)...\n";

            while (true) {
                bool stepped = machine.step();

                displayMachineState(machine);

                if (!stepped) {
                    cout << "\nProgram has halted or reached the end.\n";
                    break;
                }

                cout << "\nPress Enter to continue (or type 'q' to quit to menu): ";
                string input;
                getline(cin, input);

                if (input == "q" || input == "Q") {
                    cout << "Exiting step-by-step mode...\n";
                    break;
                }
            }

            break;
        }

        case 4: {
            displayMachineState(machine);
            break;
        }

        case 5: {
            int registerIndex;
            int value;

            cout << "Enter register index (0-F): ";
            cin >> hex >> registerIndex;

            cout << "Enter value (00-FF): ";
            cin >> hex >> value >> dec;

            if (registerIndex < 0 || registerIndex > 15 ||
                value < 0 || value > 255) {
                cout << "Invalid register index or value.\n";
            }
            else {
                machine.getRegisters().setRegister(
                    registerIndex,
                    static_cast<uint8_t>(value)
                );

                cout << "Register updated successfully.\n";
            }

            break;
        }

        case 6: {
            int address;
            int value;

            cout << "Enter memory address (00-FF): ";
            cin >> hex >> address;

            cout << "Enter value (00-FF): ";
            cin >> hex >> value >> dec;

            if (address < 0 || address > 255 ||
                value < 0 || value > 255) {
                cout << "Invalid address or value.\n";
            }
            else {
                machine.getMemory().write(
                    address,
                    static_cast<uint8_t>(value)
                );

                cout << "Memory cell updated successfully.\n";
            }

            break;
        }

        case 7: {
            machine.reset();

            programLoaded = false;

            cout << "Machine reset successfully.\n";
            break;
        }

        case 8: {
            cout << "Exiting Vole Machine Simulator...\n";
            break;
        }

        default: {
            cout << "Invalid choice. Please try again.\n";
            break;
        }

        }

    } while (choice != 8);

    return 0;
}