#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("INC ZeroPage", "[Instruction][INC][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_INC_ZP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x25;
    emulator.Mem[0x0025] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x11);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x12);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x13);
}

TEST_CASE("INC ZeroPageX", "[Instruction][INC][ZPX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_INC_ZPX;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x20;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x26;
    emulator.Mem[0x0025] = 0x10;
    emulator.Reset();

    emulator.Cpu.X = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x11);

    emulator.Cpu.X = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x12);

    emulator.Cpu.X = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x13);
}

TEST_CASE("INC Absolute", "[Instruction][INC][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_INC_ABS;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x15;
    emulator.Mem[0x0002] = 0x10;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x15;
    emulator.Mem[0x0005] = 0x10;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x15;
    emulator.Mem[0x0008] = 0x10;
    emulator.Mem[0x1015] = 0x23;
    emulator.Reset();

    REQUIRE(+emulator.Mem[0x1015] == 0x23);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x24);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x25);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x26);
}

TEST_CASE("INC AbsoluteX", "[Instruction][INC][ABSX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_INC_ABSX;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x15;
    emulator.Mem[0x0002] = 0x10;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x10;
    emulator.Mem[0x0005] = 0x10;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x16;
    emulator.Mem[0x0008] = 0x0F;
    emulator.Mem[0x1015] = 0x23;
    emulator.Reset();

    emulator.Cpu.X = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x24);

    emulator.Cpu.X = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x25);

    emulator.Cpu.X = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x26);
}

TEST_CASE("DEC ZeroPage", "[Instruction][DEC][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_DEC_ZP;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x25;
    emulator.Mem[0x0025] = 0x10;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0F);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0E);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0D);
}

TEST_CASE("DEC ZeroPageX", "[Instruction][DEC][ZPX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_DEC_ZPX;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x25;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x20;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x26;
    emulator.Mem[0x0025] = 0x10;
    emulator.Reset();

    emulator.Cpu.X = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0F);

    emulator.Cpu.X = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0E);

    emulator.Cpu.X = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x0025] == 0x0D);
}

TEST_CASE("DEC Absolute", "[Instruction][DEC][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_DEC_ABS;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x15;
    emulator.Mem[0x0002] = 0x10;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x15;
    emulator.Mem[0x0005] = 0x10;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x15;
    emulator.Mem[0x0008] = 0x10;
    emulator.Mem[0x1015] = 0x23;
    emulator.Reset();

    REQUIRE(+emulator.Mem[0x1015] == 0x23);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x22);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x21);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x20);
}

TEST_CASE("DEC AbsoluteX", "[Instruction][DEC][ABSX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    constexpr auto instruction = INS_DEC_ABSX;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x15;
    emulator.Mem[0x0002] = 0x10;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x10;
    emulator.Mem[0x0005] = 0x10;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x16;
    emulator.Mem[0x0008] = 0x0F;
    emulator.Mem[0x1015] = 0x23;
    emulator.Reset();

    emulator.Cpu.X = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x22);

    emulator.Cpu.X = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x21);

    emulator.Cpu.X = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1015] == 0x20);
}