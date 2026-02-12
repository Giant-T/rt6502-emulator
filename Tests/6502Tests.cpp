#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

TEST_CASE("LDA Immediate", "[Instruction][LDA]") {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0001] = 0x17;

    emulator.Execute();

    REQUIRE(emulator.Cpu.A == 0x17);
}

TEST_CASE("LDA ZeroPage", "[Instruction][LDA]") {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem.Data[0x0001] = 0x03;
    emulator.Mem.Data[0x0002] = 0x00;
    emulator.Mem.Data[0x0003] = 0xAD;

    emulator.Execute();

    REQUIRE(emulator.Cpu.A == 0xAD);
}

TEST_CASE("LDA Absolute", "[Instruction][LDA]") {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem.Data[0x0001] = 0x05;
    emulator.Mem.Data[0x0002] = 0x00;
    emulator.Mem.Data[0x0003] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem.Data[0x0004] = 0x34;
    emulator.Mem.Data[0x0005] = 0x12;
    emulator.Mem.Data[0x1234] = 0x2A;

    emulator.Execute();
    REQUIRE(emulator.Cpu.A == 0x12);

    emulator.Execute();
    REQUIRE(emulator.Cpu.A == 0x2A);
}

TEST_CASE("STX ZeroPage", "[Instruction][STX]") {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem.Data[0x0001] = 0x34;
    emulator.Mem.Data[0x0034] = 0x2A;

    emulator.Execute();
    REQUIRE(emulator.Mem.Data[0x34] == 0x00);
}


TEST_CASE("TSX Impl", "[Instruction][TSX]") {
    RT6502::RT6502 emulator;
    emulator.Reset();
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_TSX_IMP;

    emulator.Execute();
    REQUIRE(+emulator.Cpu.X == 0xFD);
}