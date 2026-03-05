#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("PHA Impl", "[Instruction][PHA][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_PHA_IMP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Reset();

    emulator.Cpu.A = 0x25;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN - 1U);
    REQUIRE(+emulator.Mem[RT6502::CPU::STACK_POINTER_ADDRESS] == 0x25);
}

TEST_CASE("PHP Impl", "[Instruction][PHP][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_PHP_IMP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Reset();

    emulator.Cpu.PS = {1, 0, 1, 0, 0, 1, 1, 1};

    const auto psOriginal = emulator.Cpu.PS;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN - 1U);
    REQUIRE(+emulator.Mem[RT6502::CPU::STACK_POINTER_ADDRESS] == psOriginal);
}