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
std::vector<InstrFuncPtr> Execute(CPU&);

std::vector<InstrFuncPtr> Implicit(CPU& cpu);
std::vector<InstrFuncPtr> Immediate(CPU& cpu);
std::vector<InstrFuncPtr> Zeropage(CPU& cpu);
std::vector<InstrFuncPtr> Absolute(CPU& cpu);

}  // namespace RT6502::AddressingMode