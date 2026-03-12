cmake_minimum_required(VERSION 4.1.1)

project(RT6502Emulator
        VERSION 1.0.0 
        LANGUAGES CXX
)

enable_testing()

add_subdirectory(6502)
add_subdirectory(UI)
add_subdirectory(Tests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UI)
