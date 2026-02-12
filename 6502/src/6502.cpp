#include "6502/6502.h"

void RT6502::RT6502::Reset() noexcept {
    Cpu.Reset(Mem);

    // TEST: Insérer dans la mémoire
    Cpu.PC = 0x0000;
    Mem[0x0000] = 0xA9;  // LDA immediate
    Mem[0x0001] = 0x0D;
    Mem[0x0002] = 0xA5;  // LDA zeropage
    Mem[0x0003] = 0x02;
    Mem[0x0004] = 0xAD;  // LDA absolute
    Mem[0x0005] = 0x04;
    Mem[0x0006] = 0x00;
    Mem[0x0007] = 0x85;  // STA Zeropage
    Mem[0x0008] = 0x0D;  
    Mem[0x0009] = 0x86;  // STX Zeropage
    Mem[0x000A] = 0x03;
    Mem[0x000B] = 0xA9;  // LDA immediate
    Mem[0x000C] = 0x0A;
}

void RT6502::RT6502::Execute() {
    Cpu.Execute(Mem);
}
