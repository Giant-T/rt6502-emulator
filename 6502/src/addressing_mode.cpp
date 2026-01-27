#include "6502/addressing_mode.h"

#include "6502/decode.h"

std::string RT6502::AddressingMode::Format(const AddressingMode addrMode) {
    switch (addrMode) {
        case AddressingMode::Implicit:
            return "";
        case AddressingMode::Accumulator:
            return "A";
        case AddressingMode::Immediate:
            return "#${:02X}";
        case AddressingMode::Zeropage:
            return "${:02X}";
        case AddressingMode::ZeropageX:
            return "${:02X},X";
        case AddressingMode::ZeropageY:
            return "${:02X},Y";
        case AddressingMode::Relative:
            return "${:02X}";
        case AddressingMode::Absolute:
            return "${:04X}";
        case AddressingMode::AbsoluteX:
            return "${:04X},X";
        case AddressingMode::AbsoluteY:
            return "${:04X},Y";
        case AddressingMode::Indirect:
            return "(${:04X})";
        case AddressingMode::IndexedIndirect:
            return "(${:02X},X)";
        case AddressingMode::IndirectIndexed:
            return "(${:02X}),Y";
        default:
            return "";
    }
}

RT6502::Byte RT6502::AddressingMode::Execute(const AddressingMode addrMode, Word& pc, const Memory& memory) {
    switch (addrMode) {
        case AddressingMode::Implicit:
            return Implicit(pc, memory);
        // case addressing_mode::Accumulator:
        // return "A";
        case AddressingMode::Immediate:
            return Immediate(pc, memory);
        case AddressingMode::Zeropage:
            return Zeropage(pc, memory);
        // case addressing_mode::ZeropageX:
        // return "${:02X},X";
        // case addressing_mode::ZeropageY:
        // return "${:02X},Y";
        // case addressing_mode::Relative:
        // return "${:02X}";
        case AddressingMode::Absolute:
            return Absolute(pc, memory);
        // case addressing_mode::AbsoluteX:
        // return "${:04X},X";
        // case addressing_mode::AbsoluteY:
        // return "${:04X},Y";
        // case addressing_mode::Indirect:
        // return "(${:04X})";
        // case addressing_mode::IndexedIndirect:
        // return "(${:02X},X)";
        // case addressing_mode::IndirectIndexed:
        // return "(${:02X}),Y";
        default:
            throw "not implemented";
    }
}

RT6502::Byte RT6502::AddressingMode::Implicit(Word& pc, const Memory& memory) {
    return 0;
}

RT6502::Byte RT6502::AddressingMode::Immediate(Word& pc, const Memory& memory) {
    return Decode::FetchByte(pc, memory);
}

RT6502::Byte RT6502::AddressingMode::Zeropage(Word& pc, const Memory& memory) {
    const auto addr = Decode::FetchByte(pc, memory);
    return memory[addr];
}

RT6502::Byte RT6502::AddressingMode::Absolute(Word& pc, const Memory& memory) {
    return memory[Decode::FetchWord(pc, memory)];
}