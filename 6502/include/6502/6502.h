#pragma once

#include <vector>

#include "cpu.h"
#include "memory.h"

namespace RT6502 {
struct RT6502 {
    CPU Cpu;
    Memory Mem;

    std::vector<InstrFuncPtr> FonctionsToExecutes;

    void Reset() noexcept;
    void Execute();
    void ExecuteTick(const InstrFuncPtr& func);
};

}  // namespace RT6502