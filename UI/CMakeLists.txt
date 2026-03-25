cmake_minimum_required(VERSION 4.1.1)

project(UI 
        VERSION 1.0.0 
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- FTXUI ----

if (DEFINED ENV{NIX_STORE})
    find_package(ftxui REQUIRED) 
else()
    include(FetchContent)

    set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
    set(FETCHCONTENT_QUIET OFF)

    FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
        GIT_TAG v6.1.9    
    )

    FetchContent_MakeAvailable(ftxui)
endif()

# ---------------
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ressources/6502_functional_test.bin" "${CMAKE_CURRENT_BINARY_DIR}/ressources/6502_functional_test.bin" COPYONLY)

add_executable(UI)

target_sources(UI
    PRIVATE
        src/main.cpp
        src/app.cpp
)

target_include_directories(6502
    PUBLIC
        include
)

target_link_libraries(UI
    PRIVATE
        6502::6502
        ftxui::screen
        ftxui::dom
        ftxui::component
)
