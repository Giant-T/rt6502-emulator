#pragma once

#include <string>
#include <vector>

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
std::vector<QueuedInstr> Execute(CPU&);

std::vector<QueuedInstr> Implicit(CPU& cpu);
std::vector<QueuedInstr> Immediate(CPU& cpu);
std::vector<QueuedInstr> Zeropage(CPU& cpu);
std::vector<QueuedInstr> Absolute(CPU& cpu);

}  // namespace RT6502::AddressingMode