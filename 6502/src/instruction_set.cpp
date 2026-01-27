#include "6502/instruction_set.h"

/**
 *
 * @param value
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
void RT6502::InstructionSet::LDA(const Byte value, CPU& cpu, Memory&) {
    cpu.A = value;
    cpu.PS.Z = cpu.A == 0;
    cpu.PS.N = cpu.A >> 7;
}

void RT6502::InstructionSet::TSX(const Byte value, CPU& cpu, Memory&) {
    cpu.X = cpu.SP;
    cpu.PS.Z = cpu.X == 0;
    cpu.PS.N = cpu.X >> 7;
}

void RT6502::InstructionSet::PHA(Byte, CPU& cpu, Memory& memory) {
    cpu.StackPush(memory, cpu.A);
}