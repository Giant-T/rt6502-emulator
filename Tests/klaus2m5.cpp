/**
 * Il s'agit d'un test créé par Klaus2m5 pour le 6502.
 * @link https://github.com/Klaus2m5/6502_65C02_functional_tests
 */

#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"

using namespace RT6502::InstructionSet;

TEST_CASE("Klaus2m5", "") {
    RT6502::RT6502 emulator;

    REQUIRE(emulator.LoadFile(R"(ressources\6502_functional_test.bin)"));

    emulator.Reset(0x0400);

    auto lastPC = emulator.Cpu.PC;
    int pcCounter = 0;
    int globalCounter = 10000000;  // Pour se protéger d'une loop infini

    while (pcCounter <= 20 && --globalCounter > 0) {
        emulator.Execute();

        if (emulator.Cpu.PC == lastPC) {
            ++pcCounter;
        } else {
            pcCounter = 0;
            lastPC = emulator.Cpu.PC;
        }
    }

    CAPTURE(globalCounter);
    INFO(std::format("PC := {:04X}", emulator.Cpu.PC - 1));
    INFO(std::format("SP := {:02X}", emulator.Cpu.SP));
    INFO(std::format("A  := {:02X}", emulator.Cpu.A));
    INFO(std::format("X  := {:02X}", emulator.Cpu.X));
    INFO(std::format("Y  := {:02X}", emulator.Cpu.Y));
    INFO("N  := " << std::to_string(emulator.Cpu.PS.N));
    INFO("V  := " << std::to_string(emulator.Cpu.PS.V));
    INFO("B  := " << std::to_string(emulator.Cpu.PS.B));
    INFO("D  := " << std::to_string(emulator.Cpu.PS.D));
    INFO("I  := " << std::to_string(emulator.Cpu.PS.I));
    INFO("Z  := " << std::to_string(emulator.Cpu.PS.Z));
    INFO("C  := " << std::to_string(emulator.Cpu.PS.C));
    REQUIRE(emulator.Cpu.PC - 1 == 0x3469);
}