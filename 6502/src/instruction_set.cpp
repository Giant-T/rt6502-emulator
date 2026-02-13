#include "6502/instruction_set.h"

/**
 *
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
void RT6502::InstructionSet::LDA(CPU& cpu) {
    cpu.A = cpu.DataBus;
    cpu.PS.Z = cpu.A == 0;
    cpu.PS.N = cpu.A >> 7;
}

void RT6502::InstructionSet::STA(CPU& cpu) {
    cpu.DataBus = cpu.A;
}

void RT6502::InstructionSet::TSX(CPU& cpu) {
    cpu.X = cpu.SP;
    cpu.PS.Z = cpu.X == 0;
    cpu.PS.N = cpu.X >> 7;
}

void RT6502::InstructionSet::PHA(CPU& cpu) {
    cpu.DataBus = cpu.A;
    cpu.AddressBus.Low = cpu.SP;
    cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
    --cpu.SP;
}

void RT6502::InstructionSet::STX(CPU& cpu) {
    cpu.DataBus = cpu.X;
}