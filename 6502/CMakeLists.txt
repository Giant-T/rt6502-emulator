cmake_minimum_required(VERSION 4.1.1)

project(6502
        VERSION 1.0.0 
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(6502
    src/6502.cpp
)
add_library(6502::6502 ALIAS 6502)

target_include_directories(6502
    PUBLIC
        include
)