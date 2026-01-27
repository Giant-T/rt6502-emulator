#pragma once

#include <string>

#include "6502/memory.h"
#include "types.h"

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
Byte Execute(AddressingMode, Word&, const Memory&);

Byte Implicit(Word& pc, const Memory& memory);
Byte Immediate(Word& pc, const Memory& memory);
Byte Zeropage(Word& pc, const Memory& memory);
Byte Absolute(Word& pc, const Memory& memory);

}  // namespace RT6502::AddressingMode