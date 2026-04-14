#pragma once

#include <array>
#include <utility>

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

constexpr const std::string_view& Format(const AddressingMode addrMode) {
    return FORMATS_LIST[static_cast<Byte>(addrMode)];
}

constexpr QueuedInstr Execute(const AddressingMode addressingMode) {
    switch (addressingMode) {
        case AddressingMode::Implicit:
            return Implicit;
        case AddressingMode::Accumulator:
            return Accumulator;
        case AddressingMode::Immediate:
            return Immediate;
        case AddressingMode::Zeropage:
            return Zeropage;
        case AddressingMode::ZeropageX:
            return ZeropageX;
        case AddressingMode::ZeropageY:
            return ZeropageY;
        case AddressingMode::Relative:
            return Relative;
        case AddressingMode::Absolute:
            return Absolute;
        case AddressingMode::AbsoluteX:
            return AbsoluteX;
        case AddressingMode::AbsoluteY:
            return AbsoluteY;
        case AddressingMode::Indirect:
            return Indirect;
        case AddressingMode::IndexedIndirect:
            return IndexedIndirect;
        case AddressingMode::IndirectIndexed:
            return IndirectIndexed;
        default:
            std::unreachable();
    }
}

}  // namespace RT6502::AddressingMode
