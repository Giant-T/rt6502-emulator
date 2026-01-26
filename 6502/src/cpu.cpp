#include "6502/cpu.h"

#include "6502/decode.h"

rt6502::CPU::CPU() : PC(0), SP(0), A(0), X(0), Y(0), PS() {
}

void rt6502::CPU::reset(Memory& memory) noexcept {
    PC = 0xFFFC;  // Adresse du Reset Vector
    SP = 0xFD;    // TODO: Revalider
    PS = {};
    A = X = Y = 0;

    memory.init();
}

void rt6502::CPU::execute(Memory& memory) {
    // Récupérer l'instruction
    const auto inst = decode::decode(PC, memory);

    // Exécuter l'instruction
    inst.info.func(inst.param, *this);
}