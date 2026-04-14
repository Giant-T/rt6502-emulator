#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "6502/6502.h"
#include "6502/instruction_set.h"

using namespace RT6502::InstructionSet;

TEST_CASE("Benchmark Single Instr", "[Benchmark]") {
    RT6502::RT6502 emulator;

    // Remplir la mémoire avec la même instruction
    for (unsigned int i = 0; i < RT6502::Memory::MAX_MEMORY;) {
        emulator.Mem[i++] = INS_LDA_IMM;
        emulator.Mem[i++] = 0x17;
    }

    emulator.Reset();

    BENCHMARK("LDA 0x17") {
        emulator.Execute();
    };
}

TEST_CASE("Benchmark Single Cycle", "[Benchmark]") {
    RT6502::RT6502 emulator;

    // Remplir la mémoire avec la même instruction
    for (unsigned int i = 0; i < RT6502::Memory::MAX_MEMORY;) {
        emulator.Mem[i++] = INS_TXA_IMP;
    }

    emulator.Reset();

    BENCHMARK("TXA") {
        emulator.ExecuteCycle();
    };
}