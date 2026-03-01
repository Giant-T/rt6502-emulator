#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

TEST_CASE("LDX Immediate", "[Instruction][LDX][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0005] = 0xAD;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0007] = 0xFF;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x17);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0xAD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0xFF);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("LDX ZeroPage", "[Instruction][LDX][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDX_ZP;
    emulator.Mem[0x0001] = 0xA1;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_LDX_ZP;
    emulator.Mem[0x0003] = 0xA2;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDX_ZP;
    emulator.Mem[0x0005] = 0xA3;
    emulator.Mem[0x00A1] = 0x12;
    emulator.Mem[0x00A2] = 0x23;
    emulator.Mem[0x00A3] = 0x34;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x23);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x34);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("LDX Absolute", "[Instruction][LDX][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDX_ABS;
    emulator.Mem[0x0001] = 0x05;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0003] = RT6502::InstructionSet::INS_LDX_ABS;
    emulator.Mem[0x0004] = 0x34;
    emulator.Mem[0x0005] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0x2A);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("LDA Immediate", "[Instruction][LDA][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0005] = 0xAD;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0007] = 0xFF;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x17);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0xAD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0xFF);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("LDA ZeroPage", "[Instruction][LDA][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem[0x0001] = 0xA1;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem[0x0003] = 0xA2;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem[0x0005] = 0xA3;
    emulator.Mem[0x00A1] = 0x12;
    emulator.Mem[0x00A2] = 0x23;
    emulator.Mem[0x00A3] = 0x34;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x23);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x34);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("LDA Absolute", "[Instruction][LDA][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem[0x0001] = 0x05;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0003] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem[0x0004] = 0x34;
    emulator.Mem[0x0005] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x2A);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("STX ZeroPage", "[Instruction][STX][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem[0x0005] = 0x35;
    emulator.Mem[0x0034] = 0x2A;
    emulator.Mem[0x0035] = 0xAB;
    emulator.Reset();

    emulator.Cpu.X = 0x12;

    emulator.Execute();
    cyclesCounters += emulator.Cpu.IR->Cycles;
    bytesCounters += emulator.Cpu.IR->Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x34] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x34] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x35] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("TSX Impl", "[Instruction][TSX][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_TSX_IMP;
    emulator.Mem[0x0001] = RT6502::InstructionSet::INS_TSX_IMP;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_TSX_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("PHA Impl", "[Instruction][PHA][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_PHA_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x25);
    REQUIRE(+emulator.Cpu.SP == 0xFD);
    REQUIRE(+emulator.Mem[0x01FD] == 0x00);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.SP == 0xFC);
    REQUIRE(+emulator.Mem[0x01FD] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("INC ZeroPage", "[Instruction][INC][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem[0x0005] = 0x25;
    emulator.Mem[0x0025] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x0025] == 0x11);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x0025] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x0025] == 0x13);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("INC Absolute", "[Instruction][INC][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem[0x0001] = 0x15;
    emulator.Mem[0x0002] = 0x10;
    emulator.Mem[0x0003] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem[0x0004] = 0x15;
    emulator.Mem[0x0005] = 0x10;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem[0x0007] = 0x15;
    emulator.Mem[0x0008] = 0x10;
    emulator.Mem[0x1015] = 0x23;
    emulator.Reset();

    REQUIRE(+emulator.Mem[0x1015] == 0x23);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1015] == 0x24);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1015] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1015] == 0x26);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("STA ZeroPage", "[Instruction][STA][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_STA_ZP;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0005] = 0x25;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_STA_ZP;
    emulator.Mem[0x0007] = 0x34;
    emulator.Mem[0x0034] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x34] == 0x17);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.Cpu.A == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x34] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("STA Absolute", "[Instruction][STA][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_STA_ABS;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = 0x12;
    emulator.Mem[0x0005] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0006] = 0x25;
    emulator.Mem[0x0007] = RT6502::InstructionSet::INS_STA_ABS;
    emulator.Mem[0x0008] = 0x34;
    emulator.Mem[0x0009] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1234] == 0x17);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.Cpu.A == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1234] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("STX Absolute", "[Instruction][STX][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_STX_ABS;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = 0x12;
    emulator.Mem[0x0005] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0006] = 0x25;
    emulator.Mem[0x0007] = RT6502::InstructionSet::INS_STX_ABS;
    emulator.Mem[0x0008] = 0x34;
    emulator.Mem[0x0009] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1234] == 0x17);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.Cpu.X == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem[0x1234] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("JMP Absolute", "[Instruction][JMP][ABS]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_JMP_ABS;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x0003] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0004] = 0x15;

    emulator.Mem[0x0101] = RT6502::InstructionSet::INS_JMP_ABS;
    emulator.Mem[0x0102] = 0x03;
    emulator.Mem[0x0103] = 0x00;

    emulator.Mem[0x1234] = RT6502::InstructionSet::INS_JMP_ABS;
    emulator.Mem[0x1235] = 0x01;
    emulator.Mem[0x1236] = 0x01;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JMP_ABS).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JMP_ABS).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0101 + 1);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JMP_ABS).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0003 + 1);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0005 + 1);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);
}