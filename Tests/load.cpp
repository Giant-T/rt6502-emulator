#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

struct Params {
    Opcodes Instruction;
    RT6502::Byte& Reg;
};

TEST_CASE("LDA LDX LDY Immediate", "[Instruction][LDX][LDA][LDY][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_LDA_IMM, emulator.Cpu.A},
        Params{INS_LDX_IMM, emulator.Cpu.X},
        Params{INS_LDY_IMM, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x17;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0x25;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xAD;
    emulator.Mem[0x0006] = instruction;
    emulator.Mem[0x0007] = 0xFF;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x17);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x25);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xAD);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xFF);
}

TEST_CASE("LDA LDX LDY ZeroPage", "[Instruction][LDX][LDA][LDY][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_LDA_ZP, emulator.Cpu.A},
        Params{INS_LDX_ZP, emulator.Cpu.X},
        Params{INS_LDY_ZP, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0xA1;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0xA2;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xA3;

    emulator.Mem[0x00A1] = 0x12;
    emulator.Mem[0x00A2] = 0x23;
    emulator.Mem[0x00A3] = 0x34;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x23);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x34);
}

TEST_CASE("LDA LDX LDY ZeroPageXY", "[Instruction][LDX][LDX][LDY][ZPX][ZPY]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        RT6502::Byte& Reg;
        RT6502::Byte& IndexReg;
    };

    const auto [instruction, reg, index_reg] = GENERATE_REF(
        Params{INS_LDA_ZPX, emulator.Cpu.A, emulator.Cpu.X},
        Params{INS_LDX_ZPY, emulator.Cpu.X, emulator.Cpu.Y},
        Params{INS_LDY_ZPX, emulator.Cpu.Y, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0xA1;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0xA2;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xA3;

    emulator.Mem[0x00A1] = 0x12;
    emulator.Mem[0x00A7] = 0x23;
    emulator.Mem[0x00A2] = 0x34;
    emulator.Reset();

    index_reg = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    index_reg = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x23);

    index_reg = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x34);
}

TEST_CASE("LDA LDX LDY Absolute", "[Instruction][LDX][LDA][LDY][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_LDA_ABS, emulator.Cpu.A},
        Params{INS_LDX_ABS, emulator.Cpu.X},
        Params{INS_LDY_ABS, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x22;
    emulator.Mem[0x0002] = 0x11;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x34;
    emulator.Mem[0x0005] = 0x12;

    emulator.Mem[0x1122] = 0x12;
    emulator.Mem[0x1234] = 0x2A;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x2A);
}

TEST_CASE("LDA LDX LDY AbsoluteXY", "[Instruction][LDX][LDA][LDY][ABSX][ABSY]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        RT6502::Byte& Reg;
        RT6502::Byte& IndexReg;
    };

    const auto [instruction, reg, index_reg] = GENERATE_REF(
        Params{INS_LDA_ABSX, emulator.Cpu.A, emulator.Cpu.X},
        Params{INS_LDA_ABSY, emulator.Cpu.A, emulator.Cpu.Y},
        Params{INS_LDX_ABSY, emulator.Cpu.X, emulator.Cpu.Y},
        Params{INS_LDY_ABSX, emulator.Cpu.Y, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x22;
    emulator.Mem[0x0002] = 0x11;
    emulator.Mem[0x0003] = instruction;
    emulator.Mem[0x0004] = 0x34;
    emulator.Mem[0x0005] = 0x12;

    emulator.Mem[0x1127] = 0x12;
    emulator.Mem[0x1333] = 0x2A;
    emulator.Reset();

    index_reg = 0x05;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x12);

    index_reg = 0xFF;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    cyclesCounters++;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x2A);
}

TEST_CASE("LDA IndexedIndirect", "[Instruction][LDX][INDX]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        RT6502::Byte& Reg;
        RT6502::Byte& IndexReg;
    };

    const auto [instruction, reg, index_reg] = GENERATE_REF(
        Params{INS_LDA_INDX, emulator.Cpu.A, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0xA0;
    emulator.Mem[0x0002] = instruction;
    emulator.Mem[0x0003] = 0xA0;
    emulator.Mem[0x0004] = instruction;
    emulator.Mem[0x0005] = 0xA0;

    emulator.Mem[0x009E] = 0x67;
    emulator.Mem[0x009F] = 0x45;
    emulator.Mem[0x00A0] = 0x34;
    emulator.Mem[0x00A1] = 0x12;

    emulator.Mem[0x00A4] = 0xBB;
    emulator.Mem[0x00A5] = 0xAA;

    emulator.Mem[0x1234] = 0x15;
    emulator.Mem[0xAABB] = 0x25;
    emulator.Mem[0x4567] = 0x35;
    emulator.Reset();

    index_reg = 0x00;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x15);

    index_reg = 0x04;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x25);


    index_reg = 0xFE;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x35);
}