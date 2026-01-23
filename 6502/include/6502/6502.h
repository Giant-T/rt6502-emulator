#pragma once

#include "cpu.h"
#include "memory.h"

namespace rt6502 {
struct rt6502 {
    CPU cpu;
    Memory memory;

    void reset() noexcept;
    void execute();
};

}  // namespace rt6502