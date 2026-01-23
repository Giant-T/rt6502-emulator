#include "6502/cpu.h"

rt6502::CPU::CPU() : PC(0), SP(0), A(0), X(0), Y(0), PS() {
}

void rt6502::CPU::reset(Memory& memory) noexcept {
    PC = 0xFFFC;
    SP = 0xFD;  // TODO: Revalider
    PS = {};
    A = X = Y = 0;

    memory.init();
}