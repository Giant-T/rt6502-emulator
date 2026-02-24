#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

TEST_CASE("LDA Immediate", "[Instruction][LDA]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0001] = 0x17;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0003] = 0x25;
    emulator.Mem.Data[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0005] = 0xAD;
    emulator.Mem.Data[0x0006] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0007] = 0xFF;
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

TEST_CASE("LDA ZeroPage", "[Instruction][LDA]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem.Data[0x0001] = 0xA1;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem.Data[0x0003] = 0xA2;
    emulator.Mem.Data[0x0004] = RT6502::InstructionSet::INS_LDA_ZP;
    emulator.Mem.Data[0x0005] = 0xA3;
    emulator.Mem.Data[0x00A1] = 0x12;
    emulator.Mem.Data[0x00A2] = 0x23;
    emulator.Mem.Data[0x00A3] = 0x34;
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

TEST_CASE("LDA Absolute", "[Instruction][LDA]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem.Data[0x0001] = 0x05;
    emulator.Mem.Data[0x0002] = 0x00;
    emulator.Mem.Data[0x0003] = RT6502::InstructionSet::INS_LDA_ABS;
    emulator.Mem.Data[0x0004] = 0x34;
    emulator.Mem.Data[0x0005] = 0x12;
    emulator.Mem.Data[0x1234] = 0x2A;
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

TEST_CASE("STX ZeroPage", "[Instruction][STX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem.Data[0x0001] = 0x34;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem.Data[0x0003] = 0x34;
    emulator.Mem.Data[0x0004] = RT6502::InstructionSet::INS_STX_ZP;
    emulator.Mem.Data[0x0005] = 0x35;
    emulator.Mem.Data[0x0034] = 0x2A;
    emulator.Mem.Data[0x0035] = 0xAB;
    emulator.Reset();

    emulator.Cpu.X = 0x12;

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x34] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x34] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STX_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x35] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("TSX Impl", "[Instruction][TSX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_TSX_IMP;
    emulator.Mem.Data[0x0001] = RT6502::InstructionSet::INS_TSX_IMP;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_TSX_IMP;
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

TEST_CASE("PHA Impl", "[Instruction][PHA]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0001] = 0x25;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_PHA_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.A == 0x25);
    REQUIRE(+emulator.Cpu.SP == 0xFD);
    REQUIRE(+emulator.Mem.Data[0x01FD] == 0x00);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Cpu.SP == 0xFC);
    REQUIRE(+emulator.Mem.Data[0x01FD] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("INC ZeroPage", "[Instruction][INC]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem.Data[0x0001] = 0x25;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem.Data[0x0003] = 0x25;
    emulator.Mem.Data[0x0004] = RT6502::InstructionSet::INS_INC_ZP;
    emulator.Mem.Data[0x0005] = 0x25;
    emulator.Mem.Data[0x0025] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x0025] == 0x11);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x0025] == 0x12);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x0025] == 0x13);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("INC ABS", "[Instruction][INC]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem.Data[0x0001] = 0x15;
    emulator.Mem.Data[0x0002] = 0x10;
    emulator.Mem.Data[0x0003] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem.Data[0x0004] = 0x15;
    emulator.Mem.Data[0x0005] = 0x10;
    emulator.Mem.Data[0x0006] = RT6502::InstructionSet::INS_INC_ABS;
    emulator.Mem.Data[0x0007] = 0x15;
    emulator.Mem.Data[0x0008] = 0x10;
    emulator.Mem.Data[0x1015] = 0x23;
    emulator.Reset();

    REQUIRE(+emulator.Mem.Data[0x1015] == 0x23);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x1015] == 0x24);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x1015] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x1015] == 0x26);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}

TEST_CASE("STA ZeroPage", "[Instruction][STA]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem.Data[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0001] = 0x17;
    emulator.Mem.Data[0x0002] = RT6502::InstructionSet::INS_STA_ZP;
    emulator.Mem.Data[0x0003] = 0x34;
    emulator.Mem.Data[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem.Data[0x0005] = 0x25;
    emulator.Mem.Data[0x0006] = RT6502::InstructionSet::INS_STA_ZP;
    emulator.Mem.Data[0x0007] = 0x34;
    emulator.Mem.Data[0x0034] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_STA_ZP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.FonctionsToExecutes.empty());
    REQUIRE(+emulator.Mem.Data[0x34] == 0x17);
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
    REQUIRE(+emulator.Mem.Data[0x34] == 0x25);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}