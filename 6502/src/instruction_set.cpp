#include "6502/instruction_set.h"

/**
 *
 * @param value
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
void rt6502::instruction_set::LDA(const Byte value, CPU& cpu) {
    cpu.A = value;
    cpu.PS.Z = cpu.A == 0;
    cpu.PS.N = cpu.A >> 7;
}