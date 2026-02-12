#include "6502/6502.h"

#include "6502/instruction_set.h"

void RT6502::RT6502::Reset() noexcept {
    Cpu.Reset(Mem);

    // TEST: Insérer dans la mémoire
    Cpu.PC = 0x0000;
    Mem[0x0000] = InstructionSet::INS_LDA_IMM;  // LDA immediate
    Mem[0x0001] = 0x0D;
    Mem[0x0002] = InstructionSet::INS_LDA_ZP;  // LDA zeropage
    Mem[0x0003] = 0x02;
    Mem[0x0004] = InstructionSet::INS_LDA_ABS;  // LDA absolute
    Mem[0x0005] = 0x04;
    Mem[0x0006] = 0x00;
    Mem[0x0007] = InstructionSet::INS_STA_ZP;  // STA Zeropage
    Mem[0x0008] = 0x0D;
    Mem[0x0009] = InstructionSet::INS_STX_ZP;  // STX Zeropage
    Mem[0x000A] = 0x03;
    Mem[0x000B] = InstructionSet::INS_LDA_IMM;  // LDA immediate
    Mem[0x000C] = 0x0A;
}

void RT6502::RT6502::Execute() {
    Cpu.Execute(Mem);
}
