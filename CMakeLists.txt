cmake_minimum_required(VERSION 3.16)
project(VoleGUI CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Put this file next to the backend files (Machine.cpp, CPU.cpp, ...).
# The command-line main.cpp is NOT included; gui_main.cpp replaces it.
add_executable(VoleGUI
    gui_main.cpp MainWindow.cpp MainWindow.h
    Machine.cpp CPU.cpp Instruction.cpp MemoryBus.cpp
    Screen.cpp ProgramLoader.cpp InstructionValidator.cpp)

target_link_libraries(VoleGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
