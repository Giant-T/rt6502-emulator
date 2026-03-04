#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

struct Params {
    RT6502::Byte Instruction;
    RT6502::Byte& Reg;
};

TEST_CASE("LDA LDX LDY Immediate", "[Instruction][LDX][LDA][LDY][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{RT6502::InstructionSet::INS_LDA_IMM, emulator.Cpu.A},
        Params{RT6502::InstructionSet::INS_LDX_IMM, emulator.Cpu.X}
    );

    INFO(RT6502::InstructionSet::OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xAD;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0xFF;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x17);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x25);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xAD);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xFF);
}

TEST_CASE("LDA LDX LDY ZeroPage", "[Instruction][LDX][LDA][LDY][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{RT6502::InstructionSet::INS_LDA_ZP, emulator.Cpu.A},
        Params{RT6502::InstructionSet::INS_LDX_ZP, emulator.Cpu.X}
    );

    INFO(RT6502::InstructionSet::OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0xA1;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0xA2;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xA3;
    emulator.Mem[0x00A1] = 0x12;
    emulator.Mem[0x00A2] = 0x23;
    emulator.Mem[0x00A3] = 0x34;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x23);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x34);
}

TEST_CASE("LDA LDX LDY Absolute", "[Instruction][LDX][LDA][LDY][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{RT6502::InstructionSet::INS_LDA_ABS, emulator.Cpu.A},
        Params{RT6502::InstructionSet::INS_LDX_ABS, emulator.Cpu.X}
    );

    INFO(RT6502::InstructionSet::OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x05;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x34;
    emulator.Mem[0x0005] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x2A);
}
