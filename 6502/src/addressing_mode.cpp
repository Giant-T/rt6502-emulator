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
        case AddressingMode::AbsoluteX:
            return AbsoluteX(cpu);
        case AddressingMode::AbsoluteY:
            return AbsoluteY(cpu);
        case AddressingMode::Indirect:
            return Indirect(cpu);
        case AddressingMode::IndexedIndirect:
            return IndexedIndirect(cpu);
        case AddressingMode::IndirectIndexed:
            return IndirectIndexed(cpu);
        default:
            throw "Addressing mode not implemented";
    }
}

RT6502::QueuedInstr RT6502::AddressingMode::Implicit(CPU& cpu) {
    return cpu.IR->Func;  // Dummy read, Car on ne bouge pas le PC
}

RT6502::QueuedInstr RT6502::AddressingMode::Accumulator(CPU& cpu) {
    return cpu.IR->Func;  // Dummy read, Car on ne bouge pas le PC
}

RT6502::QueuedInstr RT6502::AddressingMode::Immediate(CPU& cpu) {
    // Simplement lire avec le PC
    cpu.AddressBus = cpu.PC++;

    return cpu.IR->Func;
}

RT6502::QueuedInstr RT6502::AddressingMode::Zeropage(CPU& cpu) {
    // Une lecture pour obtenir l'adresse dans le Zéro Page
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        // La lecture pour obtenir la valeur à l'adresse
        cpu.AddressRegister = cpu.DataBus;
        cpu.AddressBus = cpu.AddressRegister;

        if (cpu.IR->RW == Write) {
            return cpu.IR->Func(cpu);
        }

        return cpu.IR->Func;
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::ZeropageX(CPU& cpu) {
    // Une lecture pour obtenir l'adresse dans le Zéro Page
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        // Lecture à l'adresse sans ajouter X
        cpu.AddressRegister = cpu.DataBus;
        cpu.AddressBus = cpu.AddressRegister;

        return [](CPU& cpu) -> QueuedInstr {
            // On ajoute l'Index à l'adresse
            cpu.AddressRegister.Low += cpu.X;

            // La lecture pour obtenir la valeur à l'adresse + Index
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW == Write) {
                return cpu.IR->Func(cpu);
            }

            return cpu.IR->Func;
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::ZeropageY(CPU& cpu) {
    // Une lecture pour obtenir l'adresse dans le Zéro Page
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        // Lecture à l'adresse sans ajouter X
        cpu.AddressRegister = cpu.DataBus;
        cpu.AddressBus = cpu.AddressRegister;

        return [](CPU& cpu) -> QueuedInstr {
            // On ajoute l'Index à l'adresse
            cpu.AddressRegister.Low += cpu.Y;

            // La lecture pour obtenir la valeur à l'adresse + Index
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW == Write) {
                return cpu.IR->Func(cpu);
            }

            return cpu.IR->Func;
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Relative(CPU& cpu) {
    cpu.AddressBus = cpu.PC++;
    return cpu.IR->Func;
}

RT6502::QueuedInstr RT6502::AddressingMode::Absolute(CPU& cpu) {
    // Lecture pour ADL
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressRegister.Low = cpu.DataBus;

        // Lecture pour ADH
        cpu.AddressBus = cpu.PC++;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressRegister.High = cpu.DataBus;

            // Mettre dans l'adresse
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW == Write) {
                return cpu.IR->Func(cpu);
            }

            return cpu.IR->Func;
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::AbsoluteX(CPU& cpu) {
    // Lecture pour ADL
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressRegister = cpu.DataBus;

        // Lecture pour ADH
        cpu.AddressBus = cpu.PC++;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressRegister.High = cpu.DataBus;

            // On ajoute l'index
            cpu.IsOverflow = cpu.AddressRegister.Low + cpu.X > 0xFF;
            cpu.AddressRegister.Low += cpu.X;
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW & Write) {
                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High += cpu.IsOverflow;
                    cpu.AddressBus = cpu.AddressRegister;

                    if (cpu.IR->RW == RMW)
                        return cpu.IR->Func;

                    return cpu.IR->Func(cpu);
                };
            }

            if (cpu.IsOverflow) {
                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High += 1;

                    // Mettre dans l'adresse
                    cpu.AddressBus = cpu.AddressRegister;
                    return cpu.IR->Func;
                };
            }

            return cpu.IR->Func;
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::AbsoluteY(CPU& cpu) {
    // Lecture pour ADL
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressRegister = cpu.DataBus;

        // Lecture pour ADH
        cpu.AddressBus = cpu.PC++;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressRegister.High = cpu.DataBus;

            // On ajoute l'index
            cpu.IsOverflow = cpu.AddressRegister.Low + cpu.Y > 0xFF;
            cpu.AddressRegister.Low += cpu.Y;
            cpu.AddressBus = cpu.AddressRegister;

            if (cpu.IR->RW & Write) {
                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High += cpu.IsOverflow;
                    cpu.AddressBus = cpu.AddressRegister;

                    if (cpu.IR->RW == RMW)
                        return cpu.IR->Func;

                    return cpu.IR->Func(cpu);
                };
            }

            if (cpu.IsOverflow) {
                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High += 1;

                    // Mettre dans l'adresse
                    cpu.AddressBus = cpu.AddressRegister;
                    return cpu.IR->Func;
                };
            }

            return cpu.IR->Func;
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::Indirect(CPU& cpu) {
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressRegister.Low = cpu.DataBus;
        cpu.AddressBus = cpu.PC++;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressRegister.High = cpu.DataBus;
            cpu.AddressBus = cpu.AddressRegister;

            return [](CPU& cpu) -> QueuedInstr {
                cpu.AddressRegister.Low = cpu.DataBus;
                cpu.AddressBus.Low++;

                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High = cpu.DataBus;
                    cpu.AddressBus = cpu.AddressRegister;

                    return cpu.IR->Func(cpu);
                };
            };
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::IndexedIndirect(CPU& cpu) {
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressBus = cpu.DataBus;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressBus.Low += cpu.X;

            return [](CPU& cpu) -> QueuedInstr {
                cpu.AddressRegister.Low = cpu.DataBus;
                cpu.AddressBus.Low++;

                return [](CPU& cpu) -> QueuedInstr {
                    cpu.AddressRegister.High = cpu.DataBus;
                    cpu.AddressBus = cpu.AddressRegister;

                    if (cpu.IR->RW == Write) {
                        return cpu.IR->Func(cpu);
                    }

                    return cpu.IR->Func;
                };
            };
        };
    };
}

RT6502::QueuedInstr RT6502::AddressingMode::IndirectIndexed(CPU& cpu) {
    cpu.AddressBus = cpu.PC++;

    return [](CPU& cpu) -> QueuedInstr {
        cpu.AddressBus = cpu.DataBus;

        return [](CPU& cpu) -> QueuedInstr {
            cpu.AddressRegister.Low = cpu.DataBus;
            cpu.AddressBus.Low++;

            return [](CPU& cpu) -> QueuedInstr {
                cpu.AddressRegister.High = cpu.DataBus;
                cpu.AddressBus = cpu.AddressRegister;

                cpu.IsOverflow = cpu.AddressBus.Low + cpu.Y > 0xFF;
                cpu.AddressBus.Low += cpu.Y;

                if (cpu.IR->RW & Write) {
                    return [](CPU& cpu) -> QueuedInstr {
                        cpu.AddressBus.High += cpu.IsOverflow;

                        if (cpu.IR->RW == RMW)
                            return cpu.IR->Func;

                        return cpu.IR->Func(cpu);
                    };
                }

                if (cpu.IsOverflow)
                    return [](CPU& cpu) -> QueuedInstr {
                        cpu.AddressBus.High += 1;
                        return cpu.IR->Func;
                    };

                return cpu.IR->Func;
            };
        };
    };
}
