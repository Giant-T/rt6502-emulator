#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("JMP Absolute", "[Instruction][JMP][ABS]") {
    size_t cyclesCounters = 0;

    constexpr auto instruction = INS_JMP_ABS;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x0003] = INS_LDX_IMM;
    emulator.Mem[0x0004] = 0x15;

    emulator.Mem[0x0101] = instruction;
    emulator.Mem[0x0102] = 0x03;
    emulator.Mem[0x0103] = 0x00;

    emulator.Mem[0x1234] = instruction;
    emulator.Mem[0x1235] = 0x01;
    emulator.Mem[0x1236] = 0x01;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0101 + 1);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0003 + 1);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0005 + 1);
    REQUIRE(+emulator.Cpu.X == 0x15);
}

TEST_CASE("JMP Indirect", "[Instruction][JMP][IND]") {
    size_t cyclesCounters = 0;

    constexpr auto instruction = INS_JMP_IND;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = 0x01;

    emulator.Mem[0x0120] = 0xFC;
    emulator.Mem[0x0121] = 0xBA;

    emulator.Mem[0xBAFC] = INS_LDX_IMM;
    emulator.Mem[0xBAFD] = 0x15;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0xBAFD);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0xBAFF);
    REQUIRE(emulator.Cpu.X == 0x15);
}

TEST_CASE("JSR Absolute", "[Instruction][JSR][ABS]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = INS_JSR_ABS;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;

    emulator.Mem[0x1234] = INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_JSR_ABS).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);

    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 1)] == 0x02);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 2)] == 0x00);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);
}

TEST_CASE("RTS Impl", "[Instruction][RTS][Impl]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = INS_JSR_ABS;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x0003] = INS_LDX_IMM;
    emulator.Mem[0x0004] = 0x37;

    emulator.Mem[0x1234] = INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;
    emulator.Mem[0x1236] = INS_RTS_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_JSR_ABS).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);

    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 1)] == 0x02);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 2)] == 0x00);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_RTS_IMP).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0003 + 1);
    REQUIRE(emulator.Cpu.SP == RT6502::CPU::STACK_POINTER_BEGIN);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x37);
}

TEST_CASE("BRK Implicit", "[Instruction][BRK][IMP]") {
    size_t cyclesCounters = 0;

    constexpr auto instruction = INS_BRK_IMP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;

    emulator.Mem[0x1234] = INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;

    emulator.Mem[0xFFFE] = 0x34;
    emulator.Mem[0xFFFF] = 0x12;
    emulator.Reset();

    auto copyFlags = emulator.Cpu.PS;
    copyFlags.B = 1;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x1234 + 1);
    REQUIRE(emulator.Cpu.PS.B);

    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 3)] == 0x00);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 2)] == 0x01);
    REQUIRE(emulator.Mem[RT6502::Word(RT6502::CPU::STACK_POINTER_PAGE, emulator.Cpu.SP + 1)] == copyFlags);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);
}

TEST_CASE("RTI Implicit", "[Instruction][RTI][IMP]") {
    size_t cyclesCounters = 0;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = INS_BRK_IMP;
    emulator.Mem[0x0001] = INS_LDX_IMM;
    emulator.Mem[0x0002] = 0x25;

    emulator.Mem[0x1234] = INS_LDX_IMM;
    emulator.Mem[0x1235] = 0x15;
    emulator.Mem[0x1236] = INS_RTI_IMP;

    emulator.Mem[0xFFFE] = 0x34;
    emulator.Mem[0xFFFF] = 0x12;
    emulator.Reset();

    auto copyFlags = emulator.Cpu.PS;
    copyFlags.B = 1;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_BRK_IMP).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x15);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_RTI_IMP).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == 0x0001 + 1);
    REQUIRE(emulator.Cpu.PS == copyFlags);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_LDX_IMM).Cycles;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(+emulator.Cpu.X == 0x25);
}