#pragma once

#include <optional>

#include "cpu.h"
#include "memory.h"

namespace RT6502 {
struct RT6502 {
    CPU Cpu;
    Memory Mem;

    size_t CyclesCounter = 0;

    std::optional<QueuedInstr> FonctionsToExecutes;

    void Reset() noexcept;
    void Execute();
    void ExecuteTick();
};

}  // namespace RT6502