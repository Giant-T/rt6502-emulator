#include "6502/6502.h"

void rt6502::rt6502::reset() noexcept {
    cpu.reset(memory);

    // TEST: Insérer dans la mémoire
    cpu.PC = 0x0000;
    memory[0x0000] = 0xA9; // LDA immediate
    memory[0x0001] = 0x0D;
    memory[0x0002] = 0xA5; // LDA zeropage
    memory[0x0003] = 0x02;
    memory[0x0004] = 0xA9; // LDA immediate
    memory[0x0005] = 0x0A;
}

void rt6502::rt6502::execute() {
    cpu.execute(memory);
}
