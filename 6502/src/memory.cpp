#include "6502/memory.h"

#include <algorithm>

rt6502::Memory::Memory() : data{} {
}

void rt6502::Memory::init() noexcept {
    std::ranges::fill(data, 0);
}

rt6502::Byte rt6502::Memory::operator[](const Word addr) const {
    return data[addr];
}

rt6502::Byte& rt6502::Memory::operator[](const Word addr) {
    return data[addr];
}