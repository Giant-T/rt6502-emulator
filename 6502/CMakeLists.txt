include(CheckCXXCompilerFlag)
cmake_minimum_required(VERSION 4.1.1)

project(6502
        VERSION 1.0.0 
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(6502
    "src/6502.cpp"
    "src/cpu.cpp"
    "src/memory.cpp" 
    "src/decode.cpp" 
    "src/instruction_set.cpp" 
    "src/addressing_mode.cpp"
    "src/frequency.cpp" 
    "src/threads/6502_thread.cpp"
    "src/stopwatch.cpp")
add_library(6502::6502 ALIAS 6502)

check_cxx_compiler_flag(-Wchanges-meaning HAS_CHANGES_MEANING)
if (HAS_CHANGES_MEANING)
    target_compile_options(6502 PRIVATE -Wno-changes-meaning)
endif()

target_include_directories(6502
    PUBLIC
        include
)
