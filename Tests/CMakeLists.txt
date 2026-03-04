cmake_minimum_required(VERSION 4.1.1)

project(UnitTests
        VERSION 1.0.0 
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (DEFINED ENV{NIX_STORE})
    find_package(Catch2 3 REQUIRED) 
else()
    include(FetchContent)

    set(FETCHCONTENT_QUIET OFF)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.13.0   
    )

    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(unit_tests "6502Tests.cpp")

target_link_libraries(unit_tests 
    PRIVATE 
        6502::6502 
        Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(unit_tests)