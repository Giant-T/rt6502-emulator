#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("BEQ Relative", "[Instruction][BEQ][Rel]") {
    size_t cyclesCounters = 0;
    size_t bytesCounters = 1;

    struct Params {
        RT6502::Byte Instruction;
        RT6502::Byte InstructionLoad;
        RT6502::Byte& Reg;
        std::function<void()> Branch;
        std::function<void()> NoBranch;
    };

    RT6502::RT6502 emulator;

    const auto [instruction, instruction_load, reg, branch, nobranch] = GENERATE_REF(
        Params{INS_BEQ_REL, INS_LDX_IMM, emulator.Cpu.X, [&] { emulator.Cpu.PS.Z = 1; }, [&] { emulator.Cpu.PS.Z = 0; }}
    );

    INFO(OPCODE_LIST.at(instruction).Name);

    emulator.Mem[0x0000] = instruction;  // Pas de branchement
    emulator.Mem[0x0001] = 0x30;
    emulator.Mem[0x0002] = instruction_load;
    emulator.Mem[0x0003] = 0x01;
    emulator.Mem[0x0004] = instruction;  // Branchement
    emulator.Mem[0x0005] = 0x31;
    emulator.Mem[0x0006] = instruction_load;
    emulator.Mem[0x0007] = 0x02;
    emulator.Mem[0x0008] = INS_JMP_ABS;  // Aller sur le bord d'une page
    emulator.Mem[0x0009] = 0xF0;
    emulator.Mem[0x000A] = 0x00;

    emulator.Mem[0x0037] = instruction_load;
    emulator.Mem[0x0038] = 0x03;
    emulator.Mem[0x0039] = instruction;  // Branchement vers l'arrière
    emulator.Mem[0x003A] = 0xCB;

    emulator.Mem[0x00F0] = instruction;  // Branchement avec traverse de page
    emulator.Mem[0x00F1] = 0x70;

    emulator.Mem[0x0162] = instruction_load;
    emulator.Mem[0x0163] = 0x04;

    emulator.Reset();

    // Scénario pas de branchement

    nobranch();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x01);

    // Scénario avec branchement

    branch();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    cyclesCounters++;
    bytesCounters = 0x38;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x03);

    // Branchement vers l'arrière

    branch();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    cyclesCounters++;
    bytesCounters = 0x07;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x02);

    // Sauter sur le bord d'une page

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(INS_JMP_ABS).Cycles;
    bytesCounters += OPCODE_LIST.at(INS_JMP_ABS).Bytes;
    bytesCounters = 0xF1;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    // Branchement avec traverse de page
    branch();

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction).Bytes;
    cyclesCounters += 2;
    bytesCounters = 0x0163;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);

    emulator.Execute();
    cyclesCounters += OPCODE_LIST.at(instruction_load).Cycles;
    bytesCounters += OPCODE_LIST.at(instruction_load).Bytes;
    REQUIRE_FALSE(emulator.FonctionsToExecutes.has_value());
    REQUIRE(emulator.CyclesCounter == cyclesCounters);
    REQUIRE(emulator.Cpu.PC == bytesCounters);
    REQUIRE(+reg == 0x04);
}