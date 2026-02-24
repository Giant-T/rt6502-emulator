#pragma once

#include <queue>

#include "cpu.h"
#include "memory.h"

namespace RT6502 {
struct RT6502 {
    CPU Cpu;
    Memory Mem;

    std::queue<InstrFuncPtr> FonctionsToExecutes;

    void Reset() noexcept;
    void Execute();
    void ExecuteTick();
};

}  // namespace RT6502