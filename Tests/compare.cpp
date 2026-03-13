#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

struct Params {
    Opcodes Instruction;
    RT6502::Byte& Reg;
};

TEST_CASE("CMP CPX CPY Immediate", "[Instruction][CMP][CPX][CPY][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_CMP_IMM, emulator.Cpu.A},
        Params{INS_CPX_IMM, emulator.Cpu.X},
        Params{INS_CPY_IMM, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x10;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x50;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x78;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x10;
    emulator.Reset();

    reg = 0x20;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0x30;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    reg = 0x78;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("CMP CPX CPY ZeroPage", "[Instruction][CMP][CPX][CPY][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_CMP_ZP, emulator.Cpu.A},
        Params{INS_CPX_ZP, emulator.Cpu.X},
        Params{INS_CPY_ZP, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x21;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0x22;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x23;

    emulator.Mem[0x0020] = 0x10;
    emulator.Mem[0x0021] = 0x50;
    emulator.Mem[0x0022] = 0x78;
    emulator.Mem[0x0023] = 0x10;
    emulator.Reset();

    reg = 0x20;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0x30;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    reg = 0x78;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("CMP CPX CPY Absolute", "[Instruction][CMP][CPX][CPY][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_CMP_ABS, emulator.Cpu.A},
        Params{INS_CPX_ABS, emulator.Cpu.X},
        Params{INS_CPY_ABS, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x20;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x21;
    emulator.Mem[0x0005] = 0x12;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0x22;
    emulator.Mem[0x0008] = 0x12;
    emulator.Mem[0x0009] = instruction;
    emulator.Mem[0x000A] = 0x23;
    emulator.Mem[0x000B] = 0x12;

    emulator.Mem[0x1220] = 0x10;
    emulator.Mem[0x1221] = 0x50;
    emulator.Mem[0x1222] = 0x78;
    emulator.Mem[0x1223] = 0x10;
    emulator.Reset();

    reg = 0x20;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0x30;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    reg = 0x78;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    reg = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}
