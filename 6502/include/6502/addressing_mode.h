#pragma once

#include <string>

#include "cpu.h"

namespace RT6502::AddressingMode {
enum class AddressingMode {
    Implicit,
    Accumulator,
    Immediate,
    Zeropage,
    ZeropageX,
    ZeropageY,
    Relative,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Indirect,
    IndexedIndirect,
    IndirectIndexed
};

std::string Format(AddressingMode);
QueuedInstr Execute(CPU&);

QueuedInstr Implicit(CPU& cpu);
QueuedInstr Accumulator(CPU& cpu);
QueuedInstr Immediate(CPU& cpu);
QueuedInstr Zeropage(CPU& cpu);
QueuedInstr ZeropageX(CPU& cpu);
QueuedInstr ZeropageY(CPU& cpu);
QueuedInstr Relative(CPU& cpu);
QueuedInstr Absolute(CPU& cpu);
QueuedInstr AbsoluteX(CPU& cpu);
QueuedInstr AbsoluteY(CPU& cpu);
QueuedInstr Indirect(CPU& cpu);

}  // namespace RT6502::AddressingMode