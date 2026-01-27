#include "6502/memory.h"

#include <algorithm>

RT6502::Memory::Memory() : Data{} {
}

void RT6502::Memory::Init() noexcept {
    std::ranges::fill(Data, 0);
}

RT6502::Byte RT6502::Memory::operator[](const Word addr) const {
    return Data[addr];
}

RT6502::Byte& RT6502::Memory::operator[](const Word addr) {
    return Data[addr];
}