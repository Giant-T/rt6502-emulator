#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("PHA PLA Impl", "[Instruction][PHA][PLA][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_PHA_IMP;
    constexpr auto instruction2 = INS_PLA_IMP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = instruction2;
    emulator.Reset();

    // PHA

    emulator.Cpu.A = 0x25;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN - 1U);
    REQUIRE(+emulator.Mem[RT6502::CPU::STACK_POINTER_ADDRESS] == 0x25);

    // PLA

    emulator.Cpu.A = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction2).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction2).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN);
    REQUIRE(+emulator.Cpu.A == 0x25);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("PHP PLP Impl", "[Instruction][PHP][PLP][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_PHP_IMP;
    constexpr auto instruction2 = INS_PLP_IMP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = instruction2;
    emulator.Reset();

    emulator.Cpu.PS = {1, 0, 1, 0, 0, 1, 1, 1};

    auto psOriginal = emulator.Cpu.PS;

    psOriginal.B = 1;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN - 1U);
    REQUIRE(emulator.Mem[RT6502::CPU::STACK_POINTER_ADDRESS] == psOriginal);

    // PLP

    emulator.Cpu.PS = {0, 0, 0, 0, 0, 0, 0, 0};

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction2).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction2).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN);
    REQUIRE(emulator.Cpu.PS == psOriginal);
}
