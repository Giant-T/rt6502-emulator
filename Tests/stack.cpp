#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

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
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.A == 0x25);
    REQUIRE(+emulator.Cpu.SP == 0xFD);
    REQUIRE(+emulator.Mem[0x01FD] == 0x00);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_PHA_IMP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.SP == 0xFC);
    REQUIRE(+emulator.Mem[0x01FD] == 0x25);
}