cmake_minimum_required(VERSION 3.16)
project(WasmTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Mandatory for Separate Header/Source files ---
# This tells CMake to automatically run MOC on headers containing the Q_OBJECT macro.
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# --- Define the Executable with src/ prefix ---
qt_add_executable(WasmTest
    src/main.cpp
    src/RadarSimulator.cpp
    src/RadarSimulator.h
    src/RadarTestWindow.cpp
    src/RadarTestWindow.h
)

# --- Include Directory Setup ---
# This allows you to use #include "RadarSimulator.h" instead of #include "src/RadarSimulator.h"
target_include_directories(WasmTest PRIVATE src)

target_link_libraries(WasmTest PRIVATE Qt6::Widgets)
