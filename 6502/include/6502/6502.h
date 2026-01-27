#pragma once

#include "cpu.h"
#include "memory.h"

namespace RT6502 {
struct RT6502 {
    CPU Cpu;
    Memory Memory;

    void Reset() noexcept;
    void Execute();
};

}  // namespace RT6502