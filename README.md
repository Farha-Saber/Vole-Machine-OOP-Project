# Vole Machine Simulator

A C++17 implementation of the **Vole Machine Simulator**, developed for CS213 – Object-Oriented Programming, Assignment 2 (Part 3: GUI).

The project provides two interfaces:
- **Console Interface:** A command-line simulator.
- **Graphical User Interface:** A desktop application built using Qt Widgets.

---

## 1. Project Information

**University:** Cairo University  
**Faculty:** Faculty of Computers and Artificial Intelligence  
**Course:** CS213 – Object-Oriented Programming  
**Instructor:** Dr. Mohammad El-Ramly  
**Sections:** S15, S16  

### Team Members

| Name | Student ID |
|---|---|
| Fatma Mohamed | 20250464 |
| Farha Saber | 20250469 |
| Jana Hossam | 20251098 |
| Kenzy Medhat | 20251297 |

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

## 3. Project Structure

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

### Console Interface

| File | Responsibility |
|---|---|
| `main.cpp` | Implements the command-line menu and user interaction. |

### Additional Folders

- `sample_programs/` – Example Vole programs used for testing.
- `screenshots/` – Screenshots of the GUI and program execution.

---

## 4. Requirements

### Console Version

- C++17 compatible compiler.
- GCC / MinGW or another compatible C++ compiler.

### GUI Version

- Qt 6 with the Widgets module.
- CMake 3.16 or newer.
- C++17 compatible compiler.
- A compatible Qt Kit (the project was tested with Qt 6.12.0 and MinGW 64-bit).

---

## 5. How to Build and Run

### A. GUI Version – Qt Creator

1. Extract the project folder.
2. Open **Qt Creator**.
3. Select **File → Open File or Project**.
4. Choose `CMakeLists.txt` from the project folder.
5. Select the appropriate Qt Kit (for example, Desktop Qt 6.12.0 MinGW 64-bit).
6. Click **Configure Project**.
7. Press the green **Run** button or use `Ctrl + R`.

**Troubleshooting**

If Qt Creator displays `Cannot find source file`:

1. Make sure you opened the correct `CMakeLists.txt`.
2. Verify that it is located in the same project directory as `gui_main.cpp` and `MainWindow.cpp`.
3. Select **Build → Clear CMake Configuration**.
4. Run CMake configuration again.

### B. Console Version – Without Qt

Open a terminal in the project directory and compile using:

```bash
g++ -std=c++17 main.cpp Machine.cpp CPU.cpp Instruction.cpp MemoryBus.cpp Screen.cpp ProgramLoader.cpp InstructionValidator.cpp -o vole
```

Run the application:

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

---

## 6. How to Use the GUI

### Program Loading

- Enter the starting address in hexadecimal (an even address between `00` and `FE`).
- Type a four-digit instruction and press **STORE** to write it into memory.
- Alternatively, use **Browse** to select a program file and then click **Load Program**.

### Execution Controls

- **Run (F5):** Executes instructions until the machine halts or reaches the execution step limit.
- **Step (F10):** Executes one instruction at a time.
- **Reset CPU:** Resets the CPU state.
- **Reset Memory:** Clears the memory.

### CPU Registers

Displays all 16 registers (R0–RF), the Program Counter (PC), and the Instruction Register (IR).

Double-click a register to edit its value.

### Memory Grid

Displays all 256 memory cells.

- Each row and column represents one hexadecimal digit of the address.
- Double-click a cell to edit its value.
- Orange indicates the instruction at the current PC.
- Green indicates a recently changed memory cell.
- The **Heatmap** option visualizes memory values using different brightness levels.

### Program Listing

Displays the loaded program in a readable format. The `>` marker indicates the next instruction to be executed.

### Screen

Displays values written to memory address `FF`.

### Additional Features

- **Theme Button:** Switches between available color themes.
- **Help Button:** Opens a short help window.
- **Status Bar:** Displays status messages and errors.

---

## 7. Program File Format

A program file contains one instruction per line.

Each instruction must consist of four hexadecimal digits.

- Empty lines are ignored.
- Lines beginning with `;` are treated as comments.
- Any text after the first four instruction digits is ignored.
- Programs containing invalid instructions are rejected.

### Example Program

```text
; Adds 5 and 7 and displays the result

2005 ; R0 = 05
2107 ; R1 = 07
5201 ; R2 = R0 + R1
32FF ; Display R2
C000 ; Halt
```

The program performs the following operations:

1. Loads the value `05` into R0.
2. Loads the value `07` into R1.
3. Adds R0 and R1, storing the result in R2.
4. Writes R2 to the screen through memory address `FF`.
5. Halts execution.

---

## 8. Supported Instructions

The simulator supports the following Vole machine instructions:

| Instruction | Description |
|---|---|
| `1RXY` | Loads register R with the contents of memory cell XY. |
| `2RXY` | Loads the immediate value XY into register R. |
| `3RXY` | Stores the contents of register R in memory cell XY. |
| `40RS` | Copies the contents of register R into register S. |
| `5RST` | Adds the contents of registers S and T as two's-complement integers and stores the result in R. |
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
- 3 exponent bits using excess-4 representation.
- 4 mantissa bits.

Example:

`68 + 58 = 6C`

This represents:

`2.0 + 1.0 = 3.0`

---

## 9. Memory-Mapped Screen Output

The simulator uses memory-mapped I/O to handle screen output.

Whenever an instruction stores a value in memory address `FF`, the Memory Bus routes that value to the Screen component.

For example:

```text
32FF
```

This stores the contents of register R2 at address `FF`, causing the value to appear on the simulated screen.

Writing to other memory addresses changes memory without producing screen output.

---

## 10. Validation and Error Handling

The simulator checks several conditions to prevent invalid operations:

- Program start addresses must be even and within the valid memory range.
- Programs must fit within the available memory.
- Program instructions must contain valid hexadecimal values.
- Invalid instructions are rejected during program loading.
- Jump targets must be even addresses.
- Register indices and memory addresses must be within their valid ranges.

---

## 11. Sample Programs and Screenshots

The `sample_programs/` folder contains example programs that demonstrate different machine instructions and operations.

The `screenshots/` folder contains screenshots showing the GUI and simulator execution.

---

## 12. Technologies Used

- **C++17** – Core programming language.
- **Object-Oriented Programming** – Project architecture and component organization.
- **Qt 6 Widgets** – Graphical user interface.
- **CMake** – GUI project configuration and build system.
- **GCC / MinGW** – Compilation of the console application and Qt project.

---

## 13. Possible Future Improvements

- Add more sample programs demonstrating complex instruction sequences.
- Improve the visual representation of CPU execution.
- Add more detailed execution history and debugging tools.
- Extend the simulator with additional educational features.

---

**Developed as part of CS213 – Object-Oriented Programming, Assignment 2.**

Cairo University – Faculty of Computers and Artificial Intelligence.
