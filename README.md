# Vole Machine Simulator

A C++17 implementation of the **Vole Machine Simulator**, developed for CS213 – Object-Oriented Programming, Assignment 2 (Part 3: GUI).

The project provides two interfaces:
- **Console Interface:** A command-line simulator.
- **Graphical User Interface:** A desktop application built using Qt Widgets.

---

## 1. Project Information

**University:** Cairo University  
**Faculty:** Faculty of Computing and Artificial Intelligence  
**Course:** CS213 – Object-Oriented Programming  
**Instructor:** Dr. Mohammad El-Ramly  
**Sections:** S15, S16  

### Team Members

| Name | Seat Number |
|---|---:|
| Fatma Mohamed | 20250464 |
| Farha Saber | 20250469 |
| Jana Hossam | 20251098 |
| Kenzy Medhat | 20251297 |

### Project Deliverables

- **Documentation & Report:** [View Project Report](https://drive.google.com/file/d/1SlKV4c5cJerrr5p9MJGO8cRpnWcolpxw/view?usp=drive_link)
- **Design Comparison Video (10 Minutes):** [Watch Design Comparison Video](https://drive.google.com/file/d/1eeR3RErRdhk5Oa5woODr4EpHmtOGhurR/view?usp=drive_link)
- **GUI Demonstration Video:** [Watch GUI Demo](https://drive.google.com/file/d/1-xMju9Y04MX6sjqjEJ__tpzWDQRMQZnL/view?usp=drive_link)

### Team Work Breakdown

The project was completed collaboratively, with each team member contributing to different parts of the initial design, documentation, implementation, testing, and graphical interface.

| Team Member | Part 1 Contributions (Initial Design & Documentation) | Implementation Contributions (GitHub Code & GUI) |
|---|---|---|
| **Fatma Mohamed** | Video & Report | Machine, Screen, `main.cpp` & README |
| **Farha Saber** | Initial Design | CPU, Instruction, MemoryBus & GUI |
| **Jana Hossam** | Assembly Programmer (Testing) | ALU, Memory, Register & Testing 10 Programs |
| **Kenzy Medhat** | AI Chats & Final Design | ProgramLoader, InstructionValidator & GUI |

---

## 2. About the Project

The Vole Machine Simulator is an educational application that simulates a simple computer architecture based on the stored-program concept.

The simulated machine contains:

- **256 Memory Cells:** Each cell stores 8 bits.
- **16 General-Purpose Registers:** R0 to RF.
- **Program Counter (PC):** Holds the address of the next instruction.
- **Instruction Register (IR):** Holds the currently fetched instruction.
- **ALU:** Performs arithmetic and logical operations.
- **Memory Bus:** Handles communication between memory and other components.
- **Screen:** Displays output produced by the simulated machine.

Each instruction consists of 4 hexadecimal digits (16 bits) and is stored in two consecutive memory cells.

The project follows an object-oriented design, separating the machine components into independent classes.

---

## 3. Project Files

The project is organized into backend simulation logic, user interfaces, and supporting resources.

### Backend – Simulator Logic

| File | Responsibility |
|---|---|
| `Machine.h / Machine.cpp` | Coordinates the machine components and provides the main interface to the simulator. |
| `CPU.h / CPU.cpp` | Handles instruction fetching, decoding, execution, and CPU state. |
| `ALU.h` | Performs arithmetic and logical operations. |
| `Instruction.h / Instruction.cpp` | Decodes instruction fields and extracts operands. |
| `InstructionValidator.h / .cpp` | Checks whether instructions are valid. |
| `ProgramLoader.h / ProgramLoader.cpp` | Reads and validates program files. |
| `MemoryBus.h / MemoryBus.cpp` | Handles memory access and routes screen output. |
| `Memory.h` | Represents the machine's memory. |
| `RegisterFile.h` | Manages the 16 CPU registers. |
| `Screen.h / Screen.cpp` | Stores and displays screen output. |

### Graphical User Interface – Qt

| File | Responsibility |
|---|---|
| `gui_main.cpp` | GUI application entry point. |
| `MainWindow.h / MainWindow.cpp` | Implements the main application window and GUI interactions. |
| `CMakeLists.txt` | Defines the project configuration and build process. |

### Console Version

| File | Responsibility |
|---|---|
| `main.cpp` | Implements the command-line menu and user interaction. |

### Extra Folders

- `sample_programs/` – The Vole programs used for testing.
- `screenshots/` – GUI and execution screenshots.

---

## 4. Requirements

### GUI Version

- Qt 6 with the Widgets module.
- CMake 3.16 or newer.
- A C++17 compatible compiler.
- Tested with Qt 6.12.0 and MinGW 64-bit.

### Console Version

- A C++17 compatible compiler.
- GCC / MinGW or another compatible C++ compiler.

---

## 5. How to Build and Run the GUI (Qt Creator)

1. Extract the project folder.
2. Open Qt Creator, then select **File > Open File or Project...**
3. Select `CMakeLists.txt` inside the project folder.
4. Choose the kit **Desktop Qt 6.12.0 MinGW 64-bit** (or another compatible Qt kit).
5. Click **Configure Project**.
6. Press the green **Run** button or use `Ctrl + R`.

**Troubleshooting**

If you see `Cannot find source file`:

1. Make sure you opened the `CMakeLists.txt` located next to `gui_main.cpp` and `MainWindow.cpp`.
2. Select **Build > Clear CMake Configuration**.
3. Run CMake configuration again.

---

## 6. How to Build and Run the Console Version (No Qt Needed)

From the project folder, open a terminal and compile using:

```bash
g++ -std=c++17 main.cpp Machine.cpp CPU.cpp Instruction.cpp MemoryBus.cpp Screen.cpp ProgramLoader.cpp InstructionValidator.cpp -o vole
```

Then run:

**Windows:**

```bash
vole.exe
```

**Linux / macOS:**

```bash
./vole
```

The console menu provides the following options:

1. Load Program
2. Run Program
3. Execute One Step
4. Display Machine State
5. Edit Register
6. Edit Memory Cell
7. Reset Machine
8. Exit

- **Load:** Enter the file path (no spaces in the path) and the starting address in hexadecimal (an even number from `00` to `FE`).
- **Step by Step:** The machine state is displayed after every step. Press Enter to execute the next step, or type `q` followed by Enter to return to the menu.

---

## 7. How to Use the GUI

### Program Box

- **Address (hex):** Enter the starting address, an even number from `00` to `FE`.
- Type one instruction and press **STORE** to write it at the specified address.
- Alternatively, press **Browse** to select a program file, then click **Load Program**.

### Execution Controls

- **Run (F5):** Executes the program until HALT, with a step limit to prevent an endless loop from freezing the window.
- **Step (F10):** Executes one instruction.
- **Reset CPU:** Resets the CPU state.
- **Reset Memory:** Clears memory.

### CPU Registers

Displays R0–RF, PC, and IR. Double-click a register to edit its value.

### Memory Grid

Displays all 256 memory cells.

- Each row and column represents one hexadecimal digit of the address.
- Double-click a cell to edit it.
- **Orange:** Indicates the instruction at the current PC.
- **Green:** Indicates a recently changed cell.
- **Heatmap:** Colors memory cells according to their values; brighter colors represent larger values.

### Program Listing

Displays a readable view of the loaded program. The `>` marker indicates the next instruction to be executed.

### Screen

Displays every value stored at memory address `FF`.

### Additional Features

- **Theme Button:** Cycles through the available color themes.
- **Help Button:** Opens a short help window.
- **Status Line:** Displays messages and errors.

---

## 8. Program File Format

A program file contains one instruction per line, written as four hexadecimal digits.

- Empty lines are ignored.
- Lines beginning with `;` are treated as comments.
- Anything after the first four instruction digits on a line is ignored.
- A program containing an invalid instruction is rejected.

### Example Program

```text
; Adds 5 and 7 and displays the result

2005 ; R0 = 05
2107 ; R1 = 07
5201 ; R2 = R0 + R1
32FF ; Display R2
C000 ; Halt
```

The example program:

1. Loads `05` into R0.
2. Loads `07` into R1.
3. Adds R0 and R1, storing the result in R2.
4. Writes the value of R2 to the screen through address `FF`.
5. Halts execution.

---

## 9. Supported Instructions

The simulator supports the following Vole machine instructions:

| Instruction | Description |
|---|---|
| `1RXY` | Loads register R with the contents of memory cell XY. |
| `2RXY` | Loads the immediate value XY into register R. |
| `3RXY` | Stores the contents of register R in memory cell XY. |
| `40RS` | Copies the contents of register R into register S. |
| `5RST` | Adds registers S and T as two's-complement integers and stores the result in R. |
| `6RST` | Adds the floating-point values in registers S and T and stores the result in R. |
| `7RST` | Performs bitwise OR between registers S and T. |
| `8RST` | Performs bitwise AND between registers S and T. |
| `9RST` | Performs bitwise XOR between registers S and T. |
| `AR0X` | Rotates the contents of register R to the right X times. |
| `BRXY` | Jumps to address XY if register R equals R0. |
| `C000` | Halts the machine. |

### Floating-Point Representation

The simulator uses an 8-bit floating-point representation:

- 1 sign bit.
- 3 exponent bits (excess-4).
- 4 mantissa bits.

Example:

`68 + 58 = 6C`

This represents:

`2.0 + 1.0 = 3.0`

---

## 10. Memory-Mapped Screen Output

The simulator uses memory-mapped I/O to handle screen output.

Whenever an instruction stores a value in memory address `FF`, the Memory Bus routes that value to the Screen component.

For example:

```text
32FF
```

This instruction stores the contents of register R2 at address `FF`, causing the value to appear on the simulated screen.

Writing to any other memory address changes memory without producing screen output.

---

## 11. Validation and Error Handling

The simulator checks several conditions to prevent invalid operations:

- Program start addresses must be even and within the valid memory range.
- Programs must fit within the available memory.
- Program instructions must contain valid hexadecimal values.
- Invalid instructions are rejected during program loading.
- Jump targets must be even addresses.
- Register indices and memory addresses must be within their valid ranges.

---

## 12. Sample Programs and Screenshots

See the `sample_programs/` and `screenshots/` folders for example Vole programs, GUI screenshots, and execution results.

---

## 13. Technologies Used

- **C++17** – Core programming language.
- **Object-Oriented Programming** – Project architecture and component organization.
- **Qt 6 Widgets** – Graphical user interface.
- **CMake** – GUI project configuration and build system.
- **GCC / MinGW** – Compilation of the console application and Qt project.

---

## 14. Possible Future Improvements

- Add more sample programs demonstrating complex instruction sequences.
- Improve the visual representation of CPU execution.
- Add detailed execution history and debugging tools.
- Extend the simulator with additional educational features.

---

**Developed as part of CS213 – Object-Oriented Programming, Assignment 2.**

Cairo University – Faculty of Computing and Artificial Intelligence.
