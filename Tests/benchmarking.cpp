#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("Benchmark Single Instr", "[Benchmark]") {
    RT6502::RT6502 emulator;

    constexpr auto instruction = INS_LDA_IMM;

    // Remplir la mémoire avec la même instruction
    for (unsigned int i = 0; i < RT6502::Memory::MAX_MEMORY; i += 2) {
        emulator.Mem[i] = instruction;
        emulator.Mem[i + 1] = 0x17;
    }

    emulator.Reset();

    BENCHMARK("LDA 0x17") {
        emulator.Execute();
    };
}