#include "6502/addressing_mode.h"

#include "6502/decode.h"

std::string rt6502::addressing_mode::format(const addressing_mode addr_mode) {
    switch (addr_mode) {
        case addressing_mode::implicit:
            return "";
        case addressing_mode::accumulator:
            return "A";
        case addressing_mode::immediate:
            return "#${:02X}";
        case addressing_mode::zeropage:
            return "${:02X}";
        case addressing_mode::zeropage_x:
            return "${:02X},X";
        case addressing_mode::zeropage_y:
            return "${:02X},Y";
        case addressing_mode::relative:
            return "${:02X}";
        case addressing_mode::absolute:
            return "${:04X}";
        case addressing_mode::absolute_x:
            return "${:04X},X";
        case addressing_mode::absolute_y:
            return "${:04X},Y";
        case addressing_mode::indirect:
            return "(${:04X})";
        case addressing_mode::indexed_indirect:
            return "(${:02X},X)";
        case addressing_mode::indirect_indexed:
            return "(${:02X}),Y";
        default:
            return "";
    }
}

rt6502::Byte rt6502::addressing_mode::execute(const addressing_mode addr_mode, Word& pc, const Memory& memory) {
    switch (addr_mode) {
        // case addressing_mode::implicit:
        // return "";
        // case addressing_mode::accumulator:
        // return "A";
        case addressing_mode::immediate:
            return immediate(pc, memory);
        case addressing_mode::zeropage:
            return zeropage(pc, memory);
        // case addressing_mode::zeropage_x:
        // return "${:02X},X";
        // case addressing_mode::zeropage_y:
        // return "${:02X},Y";
        // case addressing_mode::relative:
        // return "${:02X}";
        case addressing_mode::absolute:
            return absolute(pc, memory);
        // case addressing_mode::absolute_x:
        // return "${:04X},X";
        // case addressing_mode::absolute_y:
        // return "${:04X},Y";
        // case addressing_mode::indirect:
        // return "(${:04X})";
        // case addressing_mode::indexed_indirect:
        // return "(${:02X},X)";
        // case addressing_mode::indirect_indexed:
        // return "(${:02X}),Y";
        default:
            throw "not implemented";
    }
}

rt6502::Byte rt6502::addressing_mode::immediate(Word& pc, const Memory& memory) {
    return decode::fetch_byte(pc, memory);
}

rt6502::Byte rt6502::addressing_mode::zeropage(Word& pc, const Memory& memory) {
    const auto addr = decode::fetch_byte(pc, memory);
    return memory[addr];
}

rt6502::Byte rt6502::addressing_mode::absolute(Word& pc, const Memory& memory) {
    const auto low_byte = decode::fetch_byte(pc, memory);
    const auto high_byte = decode::fetch_byte(pc, memory);
    Word addr = high_byte;
    addr <<= 8;
    addr |= low_byte;
    return memory[addr];
}