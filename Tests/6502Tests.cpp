#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

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
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_TSX_IMP).Bytes;
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(+emulator.Cpu.X == 0xFD);
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
}
