#include "6502/6502.h"

void RT6502::RT6502::Reset() noexcept {
    Cpu.Reset(Memory);

    // TEST: Insérer dans la mémoire
    Cpu.PC = 0x0000;
    Memory[0x0000] = 0xA9;  // LDA immediate
    Memory[0x0001] = 0x0D;
    Memory[0x0002] = 0xA5;  // LDA zeropage
    Memory[0x0003] = 0x02;
    Memory[0x0004] = 0xAD;  // LDA absolute
    Memory[0x0005] = 0x04;
    Memory[0x0006] = 0x00;
    Memory[0x0007] = 0xBA;  // TSX implicit
    Memory[0x0008] = 0x48;  // PHA immediate
    Memory[0x0009] = 0xA9;  // LDA immediate
    Memory[0x000A] = 0x0A;
}

void RT6502::RT6502::Execute() {
    Cpu.Execute(Memory);
}
