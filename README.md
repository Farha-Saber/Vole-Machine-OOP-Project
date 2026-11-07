==============================================================
 Vole Machine Simulator  -  CS213 Assignment 2 (Part 3: GUI)
==============================================================
Cairo University - Faculty of Computing and Artificial Intelligence
Course     : CS213 Object Oriented Programming
Instructor : Dr. Mohammad El-Ramly
Section    : S15, S16

Team
  Fatma Mohamed   20250464
  Farha Saber     20250469
  Jana Hossam     20251098
  Kenzy Medhat    20251297


1. ABOUT
--------
A simulator of the Vole machine (Brookshear, Computer Science: An
Overview). It has 256 memory cells, 16 general-purpose registers,
a Program Counter (PC) and an Instruction Register (IR).
Written in standard C++17. The GUI is built with Qt Widgets.

The screen is memory-mapped: every value stored to address FF is
shown on the screen.


2. PROJECT FILES
----------------
Backend (simulator logic)
  Machine.h / Machine.cpp                     machine facade
  CPU.h / CPU.cpp                             fetch, decode, execute
  ALU.h                                       arithmetic and logic
  Instruction.h / Instruction.cpp             instruction decoding
  InstructionValidator.h / .cpp               rejects invalid instructions
  ProgramLoader.h / ProgramLoader.cpp         reads program files
  MemoryBus.h / MemoryBus.cpp                 routes writes to FF to screen
  Memory.h, RegisterFile.h                    memory and registers
  Screen.h / Screen.cpp                       screen output log

GUI (Qt)
  gui_main.cpp, MainWindow.h, MainWindow.cpp
  CMakeLists.txt

Console version
 main.cpp
                                              command-line interface

Extra folders
  sample_programs/                            the Vole programs we tested
  screenshots/                                GUI and execution screenshots


3. REQUIREMENTS
---------------
  - Qt 6 with the Widgets module (tested with Qt 6.12.0, MinGW 64-bit)
  - CMake 3.16 or newer (the one bundled with Qt is fine)
  - A C++17 compiler (tested with MinGW g++ 13.1.0 from the Qt installer)


4. HOW TO BUILD AND RUN THE GUI (Qt Creator)
--------------------------------------------
  1. Unzip the project to a folder.
  2. Open Qt Creator, then: File > Open File or Project...
  3. Select CMakeLists.txt inside the project folder.
  4. Choose the kit "Desktop Qt 6.12.0 MinGW 64-bit" (or your Qt 6 kit)
     and click "Configure Project".
  5. Press the green Run button (or Ctrl+R).

If you see "Cannot find source file", make sure you opened the
CMakeLists.txt that is next to gui_main.cpp and MainWindow.cpp, then
use Build > Clear CMake Configuration and Run CMake again.


5. HOW TO BUILD AND RUN THE CONSOLE VERSION (no Qt needed)
----------------------------------------------------------
From the project folder:

  g++ -std=c++17 main.cpp Machine.cpp CPU.cpp Instruction.cpp MemoryBus.cpp Screen.cpp ProgramLoader.cpp InstructionValidator.cpp -o vole

Then run:  ./vole   (on Windows: vole.exe)

Console menu: 1 Load Program, 2 Run Program, 3 Execute One Step,
4 Display Machine State, 5 Edit Register, 6 Edit Memory Cell,
7 Reset Machine, 8 Exit.

  - Load: enter the file path (no spaces in the path) and the start
    address in hex (an even number from 00 to FE).
  - Step by step: the state is shown after every step; press Enter to
    run the next step, or type q then Enter to go back to the menu.


6. HOW TO USE THE GUI
---------------------
  Program box
    - Address (hex): start address, an even number from 00 to FE.
    - Type one instruction and press STORE to write it at the address.
    - Or press Browse to choose a program file, then Load Program.
  Run (F5)         runs the program until HALT (with a step limit so an
                   endless loop cannot freeze the window).
  Step (F10)       executes one instruction.
  Reset CPU        resets the CPU state.
  Reset Memory     clears memory.
  CPU Registers    shows R0-RF, PC and IR. Double-click a register to
                   edit it.
  Memory grid      256 cells (row digit + column digit = address).
                   Double-click a cell to edit it.
                   Orange = the instruction at PC, green = just changed.
  Heatmap checkbox colors memory cells by value (brighter = larger).
  Program Listing  readable view of the program. ">" marks the next
                   instruction.
  Screen           shows every value stored to address FF.
  Theme button     cycles through the available color themes.
  Help button      short help window.
  A status line at the bottom shows messages and errors.


7. PROGRAM FILE FORMAT
----------------------
One instruction per line, written as 4 hex digits. Lines that start
with ; and empty lines are ignored. Anything after the 4 digits on a
line is ignored. Example:

    ; Adds 5 and 7 and shows 12
    2005 ; R0 = 05
    2107 ; R1 = 07
    5201 ; R2 = R0 + R1
    32FF ; show R2 on the screen
    C000 ; halt

A program that contains an invalid instruction is rejected.


8. SUPPORTED INSTRUCTIONS
-------------------------
  1RXY  load R from memory cell XY
  2RXY  load R with the value XY
  3RXY  store R in memory cell XY   (3RFF writes to the screen)
  40RS  move R to S
  5RST  R = S + T (two's complement)
  6RST  R = S + T (floating point)
  7RST  R = S OR T
  8RST  R = S AND T
  9RST  R = S XOR T
  AR0X  rotate R right X times
  BRXY  jump to XY if R equals R0
  C000  halt

  Floating point format (8 bits): 1 sign bit, 3 exponent bits
  (excess-4), 4 mantissa bits. Example: 68 + 58 = 6C (2.0 + 1.0 = 3.0).


9. NOTES
--------
  - Output reaches the screen only through address FF. Writing to any
    other address (for example 3R00) changes memory but does not print.
  - Jump targets should be even addresses.
  - Invalid instructions, bad file lines, odd start addresses and
    programs that do not fit in memory are rejected when loading.


10. SAMPLE PROGRAMS AND SCREENSHOTS
-----------------------------------
See the folders sample_programs/ and screenshots/.
