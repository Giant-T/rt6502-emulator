#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

TEST_CASE("CMP Immediate", "[Instruction][CMP][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x0003] = 0x10;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0005] = 0x30;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x0007] = 0x50;
    emulator.Mem[0x0008] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0009] = 0x78;
    emulator.Mem[0x000A] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x000B] = 0x78;
    emulator.Mem[0x000C] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x000D] = 0xFF;
    emulator.Mem[0x000E] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x000F] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("CMP ZeroPage", "[Instruction][CMP][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_CMP_ZP;
    emulator.Mem[0x0003] = 0x20;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0005] = 0x30;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_CMP_ZP;
    emulator.Mem[0x0007] = 0x21;
    emulator.Mem[0x0008] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0009] = 0x78;
    emulator.Mem[0x000A] = RT6502::InstructionSet::INS_CMP_ZP;
    emulator.Mem[0x000B] = 0x22;
    emulator.Mem[0x000C] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x000D] = 0xFF;
    emulator.Mem[0x000E] = RT6502::InstructionSet::INS_CMP_ZP;
    emulator.Mem[0x000F] = 0x23;

    emulator.Mem[0x0020] = 0x10;
    emulator.Mem[0x0021] = 0x50;
    emulator.Mem[0x0022] = 0x78;
    emulator.Mem[0x0023] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("CMP Absolute", "[Instruction][CMP][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_CMP_ABS;
    emulator.Mem[0x0003] = 0x20;
    emulator.Mem[0x0004] = 0x12;
    emulator.Mem[0x0005] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0006] = 0x30;
    emulator.Mem[0x0007] = RT6502::InstructionSet::INS_CMP_ABS;
    emulator.Mem[0x0008] = 0x21;
    emulator.Mem[0x0009] = 0x12;
    emulator.Mem[0x000A] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x000B] = 0x78;
    emulator.Mem[0x000C] = RT6502::InstructionSet::INS_CMP_ABS;
    emulator.Mem[0x000D] = 0x22;
    emulator.Mem[0x000E] = 0x12;
    emulator.Mem[0x000F] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0010] = 0xFF;
    emulator.Mem[0x0011] = RT6502::InstructionSet::INS_CMP_ABS;
    emulator.Mem[0x0012] = 0x23;
    emulator.Mem[0x0013] = 0x12;

    emulator.Mem[0x1220] = 0x10;
    emulator.Mem[0x1221] = 0x50;
    emulator.Mem[0x1222] = 0x78;
    emulator.Mem[0x1223] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDA_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}
