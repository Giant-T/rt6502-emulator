#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

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
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x11);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x12);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ZP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x13);
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
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x24);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x25);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Cycles;
    bytesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_INC_ABS).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x26);
}
