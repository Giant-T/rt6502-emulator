#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

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
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JMP_ABS).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0101 + 1);
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JMP_ABS).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0003 + 1);
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    REQUIRE(emulator.Cpu.PC == 0x0005 + 1);
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);
}

TEST_CASE("JSR Absolute", "[Instruction][JSR][ABS]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_JSR_ABS;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;

    emulator.Mem[0x1234] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JSR_ABS).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);

    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 1)] == 0x03);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 2)] == 0x00);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);
}

TEST_CASE("RTS Impl", "[Instruction][RTS][Impl]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = RT6502::InstructionSet::INS_JSR_ABS;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x0003] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x0004] = 0x37;

    emulator.Mem[0x1234] = RT6502::InstructionSet::INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;
    emulator.Mem[0x1236] = RT6502::InstructionSet::INS_RTS_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_JSR_ABS).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);

    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 1)] == 0x03);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 2)] == 0x00);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_RTS_IMP).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0003 + 1);
    REQUIRE(emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN);

    emulator.Execute();
    cyclesCounters += RT6502::InstructionSet::OPCODE_LIST.at(RT6502::InstructionSet::INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x37);
}