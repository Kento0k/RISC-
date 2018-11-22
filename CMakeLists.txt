# cmake_minimum_required(VERSION <specify CMake version here>)
project(RISC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISC__ main.cpp RiscEmulatorLibrary.h execute.cpp file_parser.cpp errors.cpp debug.cpp instruction.cpp run.cpp write_to_memory.cpp)