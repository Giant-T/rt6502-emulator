#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

struct Params {
    Opcodes Instruction;
    Opcodes InstructionLoad;
    RT6502::Byte& Reg;
};

TEST_CASE("STA STX STY ZeroPage", "[Instruction][STA][STX][STY][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;

    const auto [instruction, instruction_load, reg] = GENERATE_REF(
        Params{INS_STA_ZP, INS_LDA_IMM, emulator.Cpu.A},
        Params{INS_STY_ZP, INS_LDY_IMM, emulator.Cpu.Y},
        Params{INS_STX_ZP, INS_LDX_IMM, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction_load;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = instruction_load;
    emulator.Mem[0x0005] = 0x25;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x34;
    emulator.Mem[0x0034] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x34] == +reg);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x34] == +reg);
}

TEST_CASE("STA STX STY Absolute", "[Instruction][STA][STX][STY][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;

    const auto [instruction, instruction_load, reg] = GENERATE_REF(
        Params{INS_STA_ABS, INS_LDA_IMM, emulator.Cpu.A},
        Params{INS_STY_ABS, INS_LDY_IMM, emulator.Cpu.Y},
        Params{INS_STX_ABS, INS_LDX_IMM, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction_load;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x34;
    emulator.Mem[0x0004] = 0x12;
    emulator.Mem[0x0005] = instruction_load;
    emulator.Mem[0x0006] = 0x25;
    emulator.Mem[0x0007] = instruction;
    emulator.Mem[0x0008] = 0x34;
    emulator.Mem[0x0009] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1234] == +reg);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Mem[0x1234] == +reg);
}
