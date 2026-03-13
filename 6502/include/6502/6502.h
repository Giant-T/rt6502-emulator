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

    void Reset(const Word = 0x0000) noexcept;
    void Execute();
    void ExecuteTick();

    bool LoadFile(const char*);
};

}  // namespace RT6502
