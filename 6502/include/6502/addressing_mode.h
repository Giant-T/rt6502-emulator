#pragma once

#include <string>

#include "6502/memory.h"
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
void Execute(CPU&, Memory&);

void Implicit(CPU& cpu, Memory& memory);
void Immediate(CPU& cpu, Memory& memory);
void Zeropage(CPU& cpu, Memory& memory);
void Absolute(CPU& cpu, Memory& memory);

}  // namespace RT6502::AddressingMode