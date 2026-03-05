#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

struct Params {
    Opcodes Instruction;
    RT6502::Byte& Reg;
};

TEST_CASE("ADC Immediate", "[Instruction][ADC][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_IMM, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x10;
    emulator.Reset();

    emulator.Cpu.A = 0x15;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x25);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.V);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ADC ZeroPage", "[Instruction][ADC][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_ZP, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0x50;
    emulator.Reset();

    emulator.Cpu.A = 0x50;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xA0);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.V);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("ADC Absolute", "[Instruction][ADC][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_ABS, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x1234] = 0xFF;
    emulator.Reset();

    emulator.Cpu.A = 0x01;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x00);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.V);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ASL ZeroPage", "[Instruction][ASL][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_ASL_ZP;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0xAD;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0x5A);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ASL Absolute", "[Instruction][ASL][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_ASL_ABS;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0034] = 0xAD;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0x5A);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}