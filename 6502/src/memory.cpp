#include "6502/memory.h"

#include <algorithm>

RT6502::Memory::Memory() : Data{} {
}

void RT6502::Memory::Init() noexcept {
    std::ranges::fill(Data, 0);
}

void RT6502::Memory::Read(const Word& addrBus, Byte& dataBus) const {
    dataBus = Data[addrBus];
}

void RT6502::Memory::Write(const Word& addrBus, const Byte& dataBus) {
    Data[addrBus] = dataBus;
}

RT6502::Byte RT6502::Memory::operator[](const Word addr) const {
    return Data[addr];
}

RT6502::Byte& RT6502::Memory::operator[](const Word addr) {
    return Data[addr];
}