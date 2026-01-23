#include "6502/memory.h"

#include <algorithm>

rt6502::Memory::Memory() : Data{} {
}

void rt6502::Memory::init() noexcept {
    std::ranges::fill(Data, 0);
}