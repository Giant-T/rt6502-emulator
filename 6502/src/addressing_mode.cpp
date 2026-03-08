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

RT6502::QueuedInstr RT6502::AddressingMode::Execute(CPU& cpu) {
    switch (cpu.IR->AddrMode) {
        case AddressingMode::Implicit:
            return Implicit(cpu);
        case AddressingMode::Accumulator:
            return Accumulator(cpu);
        case AddressingMode::Immediate:
            return Immediate(cpu);
        case AddressingMode::Zeropage:
            return Zeropage(cpu);
        case AddressingMode::ZeropageX:
            return ZeropageX(cpu);
        case AddressingMode::ZeropageY:
            return ZeropageY(cpu);
        case AddressingMode::Relative:
            return Relative(cpu);
        case AddressingMode::Absolute:
            return Absolute(cpu);
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
            throw std::exception("Addressing mode not implemented");
    }
}

RT6502::QueuedInstr RT6502::AddressingMode::Implicit(CPU& cpu) {
    return [&] {
        // Dummy read
        // Car on ne bouge pas le PC
        return cpu.IR->Func(cpu);
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Accumulator(CPU& cpu) {
    return [&] {
        // Dummy read
        // Car on ne bouge pas le PC
        return cpu.IR->Func(cpu);
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Immediate(CPU& cpu) {
    return [&] {
        // Simplement lire avec le PC
        cpu.AddressBus = cpu.PC++;

        return cpu.IR->Func(cpu);
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Zeropage(CPU& cpu) {
    return [&] {
        // Une lecture pour obtenir l'adresse dans le Zéro Page
        cpu.AddressBus = cpu.PC++;

        return [&] -> std::optional<QueuedInstr> {
            // La lecture pour obtenir la valeur à l'adresse
            cpu.AddressRegister = cpu.DataBus;
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW == Write) {
                return cpu.IR->Func(cpu)();
            }

            return cpu.IR->Func(cpu);
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::ZeropageX(CPU& cpu) {
    return [&] {
        // Une lecture pour obtenir l'adresse dans le Zéro Page
        cpu.AddressBus = cpu.PC++;

        return [&] {
            // Lecture à l'adresse sans ajouter X
            cpu.AddressRegister = cpu.DataBus;
            cpu.AddressBus = cpu.AddressRegister;

            return [&] -> std::optional<QueuedInstr> {
                // On ajoute l'Index à l'adresse
                cpu.AddressRegister.Low += cpu.X;

                // La lecture pour obtenir la valeur à l'adresse + Index
                cpu.AddressBus = cpu.AddressRegister;

                if (cpu.IR->RW == Write) {
                    return cpu.IR->Func(cpu)();
                }

                return cpu.IR->Func(cpu);
            };
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::ZeropageY(CPU& cpu) {
    return [&] {
        // Une lecture pour obtenir l'adresse dans le Zéro Page
        cpu.AddressBus = cpu.PC++;

        return [&] {
            // Lecture à l'adresse sans ajouter X
            cpu.AddressRegister = cpu.DataBus;
            cpu.AddressBus = cpu.AddressRegister;

            return [&] -> std::optional<QueuedInstr> {
                // On ajoute l'Index à l'adresse
                cpu.AddressRegister.Low += cpu.Y;

                // La lecture pour obtenir la valeur à l'adresse + Index
                cpu.AddressBus = cpu.AddressRegister;

                if (cpu.IR->RW == Write) {
                    return cpu.IR->Func(cpu)();
                }

                return cpu.IR->Func(cpu);
            };
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Relative(CPU& cpu) {
    return [&] {
        cpu.AddressBus = cpu.PC++;
        return cpu.IR->Func(cpu);
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Absolute(CPU& cpu) {
    return [&] {
        // Lecture pour ADL
        cpu.AddressBus = cpu.PC++;

        return [&] {
            cpu.AddressRegister = cpu.DataBus;

            // Lecture pour ADH
            cpu.AddressBus = cpu.PC++;

            return [&] -> std::optional<QueuedInstr> {
                cpu.AddressRegister.High = cpu.DataBus;

                // Mettre dans l'adresse
                cpu.AddressBus = cpu.AddressRegister;

                if (cpu.IR->RW == Write) {
                    return cpu.IR->Func(cpu)();
                }

                return cpu.IR->Func(cpu);
            };
        };
    };
}