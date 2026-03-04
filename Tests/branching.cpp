#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

TEST_CASE("BEQ Relative", "[Instruction][BEQ][Rel]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0001] = 0x11;
    emulator.Mem[0x0002] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x0003] = 0x10;
    emulator.Mem[0x0004] = RT6502::InstructionSet::INS_BEQ_REL;  // Pas de branchement
    emulator.Mem[0x0005] = 0x30;
    emulator.Mem[0x0006] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0007] = 0x01;

    emulator.Mem[0x0008] = RT6502::InstructionSet::INS_LDA_IMM;
    emulator.Mem[0x0009] = 0x10;
    emulator.Mem[0x000A] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x000B] = 0x10;
    emulator.Mem[0x000C] = RT6502::InstructionSet::INS_BEQ_REL;  // Branchement
    emulator.Mem[0x000D] = 0x30;
    emulator.Mem[0x000E] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x000F] = 0x02;

    emulator.Mem[0x003E] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x003F] = 0x03;
    emulator.Mem[0x0040] = RT6502::InstructionSet::INS_CMP_IMM;
    emulator.Mem[0x0041] = 0x10;
    emulator.Mem[0x0042] = RT6502::InstructionSet::INS_BEQ_REL;  // Branchement vers l'arrière
    emulator.Mem[0x0043] = 0xCA;

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

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.X == 0x01);

    // Scénario avec branchement

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

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Bytes;
    cyclesCounters++;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x3F);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x41);
    REQUIRE(emulator.Cpu.X == 0x03);

    // Branchement vers l'arrière
    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_CMP_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x43);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_BEQ_REL).Bytes;
    cyclesCounters++;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0F);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x11);
    REQUIRE(emulator.Cpu.X == 0x02);
}