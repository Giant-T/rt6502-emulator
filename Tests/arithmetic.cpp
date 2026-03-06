#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

struct Params {
    Opcodes Instruction;
    RT6502::Byte& Reg;
};

TEST_CASE("ADC Immediate", "[Instruction][ADC][Imm]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_IMM, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x10;
    emulator.Reset();

    emulator.Cpu.A = 0x15;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x25);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.V);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ADC ZeroPage", "[Instruction][ADC][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_ZP, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0x50;
    emulator.Reset();

    emulator.Cpu.A = 0x50;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xA0);
    REQUIRE_FALSE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.V);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("ADC Absolute", "[Instruction][ADC][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_ADC_ABS, emulator.Cpu.A}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x1234] = 0xFF;
    emulator.Reset();

    emulator.Cpu.A = 0x01;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x00);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.V);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ASL ZeroPage", "[Instruction][ASL][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_ASL_ZP;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0b10101101;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0b01011010);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("ASL Absolute", "[Instruction][ASL][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_ASL_ABS;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0034] = 0b10101101;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0b01011010);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("LSR ZeroPage", "[Instruction][LSR][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_LSR_ZP;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0b10101101;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0b01010110);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("LSR Absolute", "[Instruction][LSR][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_LSR_ABS;

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x00;
    emulator.Mem[0x0034] = 0b10101101;
    emulator.Reset();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Mem[0x0034] == 0b01010110);
    REQUIRE(emulator.Cpu.PS.C);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("INX INY Implicit", "[Instruction][INX][INY][IMP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_INX_IMP, emulator.Cpu.X},
        Params{INS_INY_IMP, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = instruction;
    emulator.Mem[0x0002] = instruction;
    emulator.Reset();

    reg = 0xFE;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xFF);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x00);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x01);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);
}

TEST_CASE("DEX DEY Implicit", "[Instruction][DEX][DEY][IMP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    const auto [instruction, reg] = GENERATE_REF(
        Params{INS_DEX_IMP, emulator.Cpu.X},
        Params{INS_DEY_IMP, emulator.Cpu.Y}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = instruction;
    emulator.Mem[0x0002] = instruction;
    emulator.Reset();

    reg = 0x02;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x01);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x00);
    REQUIRE(emulator.Cpu.PS.Z);
    REQUIRE_FALSE(emulator.Cpu.PS.N);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0xFF);
    REQUIRE_FALSE(emulator.Cpu.PS.Z);
    REQUIRE(emulator.Cpu.PS.N);
}

TEST_CASE("ORA AND EOR Immediate", "[Instruction][ORA][AND][EOR][IMM]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        std::function<RT6502::Byte(RT6502::Byte, RT6502::Byte)> Oper;
    };

    const auto [instruction, oper] = GENERATE_REF(
        Params{INS_ORA_IMM, std::bit_or()},
        Params{INS_AND_IMM, std::bit_and()},
        Params{INS_EOR_IMM, std::bit_xor()}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0b10101010;
    emulator.Reset();

    constexpr uint8_t value = 0b10010110;
    emulator.Cpu.A = value;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.A == oper(value, 0b10101010));
}

TEST_CASE("ORA AND EOR ZeroPage", "[Instruction][ORA][AND][EOR][ZP]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        std::function<RT6502::Byte(RT6502::Byte, RT6502::Byte)> Oper;
    };

    const auto [instruction, oper] = GENERATE_REF(
        Params{INS_ORA_ZP, std::bit_or()},
        Params{INS_AND_ZP, std::bit_and()},
        Params{INS_EOR_ZP, std::bit_xor()}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0034] = 0b10101010;
    emulator.Reset();

    constexpr uint8_t value = 0b10010110;
    emulator.Cpu.A = value;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.A == oper(value, 0b10101010));
}

TEST_CASE("ORA AND EOR Absolute", "[Instruction][ORA][AND][EOR][ABS]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;
    RT6502::RT6502 emulator;

    struct Params {
        Opcodes Instruction;
        std::function<RT6502::Byte(RT6502::Byte, RT6502::Byte)> Oper;
    };

    const auto [instruction, oper] = GENERATE_REF(
        Params{INS_ORA_ABS, std::bit_or()},
        Params{INS_AND_ABS, std::bit_and()},
        Params{INS_EOR_ABS, std::bit_xor()}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;
    emulator.Mem[0x0001] = 0x34;
    emulator.Mem[0x0002] = 0x12;
    emulator.Mem[0x1234] = 0b10101010;
    emulator.Reset();

    constexpr uint8_t value = 0b10010110;
    emulator.Cpu.A = value;

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(emulator.Cpu.A == oper(value, 0b10101010));
}