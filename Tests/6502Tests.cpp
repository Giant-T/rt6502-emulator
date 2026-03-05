#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("TSX Impl", "[Instruction][TSX][Impl]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    RT6502::RT6502 emulator;
    emulator.Mem[0x0000] = INS_TSX_IMP;
    emulator.Mem[0x0001] = INS_TSX_IMP;
    emulator.Mem[0x0002] = INS_TSX_IMP;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_TSX_IMP).Cycles;
    bytesCounters += OPCODE_LIST.at(INS_TSX_IMP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.X == RT6502::CPU::STACK_POINTER_BEGIN);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_TSX_IMP).Cycles;
    bytesCounters += OPCODE_LIST.at(INS_TSX_IMP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.X == RT6502::CPU::STACK_POINTER_BEGIN);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_TSX_IMP).Cycles;
    bytesCounters += OPCODE_LIST.at(INS_TSX_IMP).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+emulator.Cpu.X == RT6502::CPU::STACK_POINTER_BEGIN);
}

TEST_CASE("Clear Flags Implicit", "[Instruction][CLC][CLI][CLD][CLV][IMP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        std::function<RT6502::Byte()> Flag;
    };

    const auto [instruction, flag] = GENERATE_REF(
        Params{INS_CLC_IMP, [&] { return emulator.Cpu.PS.C; }},
        Params{INS_CLI_IMP, [&] { return emulator.Cpu.PS.I; }},
        Params{INS_CLD_IMP, [&] { return emulator.Cpu.PS.D; }},
        Params{INS_CLV_IMP, [&] { return emulator.Cpu.PS.V; }}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Reset();

    emulator.Cpu.PS = 1;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE_FALSE(flag());
}

TEST_CASE("Set Flags Implicit", "[Instruction][SEC][SEI][SED][IMP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        std::function<RT6502::Byte()> Flag;
    };

    const auto [instruction, flag] = GENERATE_REF(
        Params{INS_SEC_IMP, [&] { return emulator.Cpu.PS.C; }},
        Params{INS_SEI_IMP, [&] { return emulator.Cpu.PS.I; }},
        Params{INS_SED_IMP, [&] { return emulator.Cpu.PS.D; }}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Reset();

    emulator.Cpu.PS = 0;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(flag());
}

TEST_CASE("Transfer Implicit", "[Instruction][TXA][TYA][TXS][TAY][TAX][TSX][IMP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        RT6502::Byte& SrcReg;
        RT6502::Byte& DstReg;
    };

    const auto [instruction, src_reg, dst_reg] = GENERATE_REF(
        Params{INS_TXA_IMP, emulator.Cpu.X, emulator.Cpu.A},
        Params{INS_TYA_IMP, emulator.Cpu.Y, emulator.Cpu.A},
        Params{INS_TXS_IMP, emulator.Cpu.X, emulator.Cpu.SP},
        Params{INS_TAY_IMP, emulator.Cpu.A, emulator.Cpu.Y},
        Params{INS_TAX_IMP, emulator.Cpu.A, emulator.Cpu.X},
        Params{INS_TSX_IMP, emulator.Cpu.SP, emulator.Cpu.X}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Reset();

    src_reg = 0x15;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(dst_reg == src_reg);
}