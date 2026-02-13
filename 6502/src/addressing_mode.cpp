#include "6502/addressing_mode.h"

#include "6502/instruction_set.h"

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

void RT6502::AddressingMode::Execute(CPU& cpu, Memory& memory) {
    switch (cpu.IR->AddrMode) {
        case AddressingMode::Implicit:
            Implicit(cpu, memory);
            break;
        //  case addressing_mode::Accumulator:
        //  return "A";
        case AddressingMode::Immediate:
            Immediate(cpu, memory);
            break;
        case AddressingMode::Zeropage:
            Zeropage(cpu, memory);
            break;
            // case addressing_mode::ZeropageX:
            // return "${:02X},X";
            // case addressing_mode::ZeropageY:
            // return "${:02X},Y";
            // case addressing_mode::Relative:
            // return "${:02X}";
        case AddressingMode::Absolute:
            Absolute(cpu, memory);
            break;
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

void RT6502::AddressingMode::Implicit(CPU& cpu, Memory& memory) {
}

void RT6502::AddressingMode::Immediate(CPU& cpu, Memory& memory) {
    // Simplement lire avec le PC
    cpu.AddressBus = cpu.PC++;
    memory.Read(cpu.AddressBus, cpu.DataBus);
}

void RT6502::AddressingMode::Zeropage(CPU& cpu, Memory& memory) {
    // Une lecture pour l'adresse du Zéro Page
    cpu.AddressBus = cpu.PC++;
    memory.Read(cpu.AddressBus, cpu.DataBus);

    cpu.AddressRegister = cpu.DataBus;
    cpu.AddressBus = cpu.AddressRegister;
}

void RT6502::AddressingMode::Absolute(CPU& cpu, Memory& memory) {
    // Lecture pour ADL
    cpu.AddressBus = cpu.PC++;
    memory.Read(cpu.AddressBus, cpu.DataBus);

    cpu.AddressRegister = cpu.DataBus;

    // Lecture pour ADH
    cpu.AddressBus = cpu.PC++;
    memory.Read(cpu.AddressBus, cpu.DataBus);

    cpu.AddressRegister |= cpu.DataBus << 8;

    // Mettre dans l'adresse
    cpu.AddressBus = cpu.AddressRegister;
}