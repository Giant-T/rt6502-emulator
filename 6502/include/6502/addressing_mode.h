#pragma once

#include <string>
#include <array>

#include "cpu.h"

namespace RT6502::AddressingMode {
enum class AddressingMode : Byte {
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

using namespace std::string_view_literals;

constexpr std::array FORMATS_LIST = {
    ""sv,
    "A"sv,
    "#${:02X}"sv,
    "${:02X}"sv,
    "${:02X},X"sv,
    "${:02X},Y"sv,
    "${:02X}"sv,
    "${:04X}"sv,
    "${:04X},X"sv,
    "${:04X},Y"sv,
    "(${:04X})"sv,
    "(${:02X},X)"sv,
    "(${:02X}),Y"sv,
};

constexpr const std::string_view& Format(const AddressingMode addrMode) {
    return FORMATS_LIST[static_cast<Byte>(addrMode)];
}
std::function<QueuedInstr(CPU&)> Execute(const AddressingMode addressingMode);

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
QueuedInstr IndexedIndirect(CPU& cpu);
QueuedInstr IndirectIndexed(CPU& cpu);

}  // namespace RT6502::AddressingMode