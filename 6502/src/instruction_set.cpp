#include "6502/instruction_set.h"

/**
 *
 * @warning Ce n'est pas la bonne séquence d'exécution, mais on peut vivre avec
 */
RT6502::QueuedInstr RT6502::InstructionSet::JSR(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.PC.High;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;

            return QueuedInstr{[&] {
                cpu.RW = false;
                cpu.DataBus = cpu.PC.Low;
                cpu.AddressBus.Low = cpu.SP--;
                cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;

                return QueuedInstr{
                    [&] {
                        cpu.PC = cpu.AddressRegister;
                        return std::nullopt;
                    }
                };
            }};
        }}

    };
}

RT6502::QueuedInstr RT6502::InstructionSet::JMP(CPU& cpu) {
    return {
        {[&] {
            cpu.PC = cpu.AddressBus;
            return std::nullopt;
        }}
    };
}

/**
 *
 * @warning Ce n'est pas la bonne séquence d'exécution, mais on peut vivre avec
 */
RT6502::QueuedInstr RT6502::InstructionSet::RTS(CPU& cpu) {
    return {
        {[&] {
            cpu.SP++;

            return QueuedInstr{
                [&] {
                    cpu.AddressBus.Low = cpu.SP++;
                    cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;

                    return QueuedInstr{
                        [&] {
                            cpu.AddressRegister.Low = cpu.DataBus;
                            cpu.AddressBus.Low = cpu.SP;
                            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;

                            return QueuedInstr{
                                [&] {
                                    cpu.AddressRegister.High = cpu.DataBus;

                                    return QueuedInstr{
                                        [&] {
                                            cpu.PC = cpu.AddressRegister;
                                            return std::nullopt;
                                        }
                                    };
                                }
                            };
                        }
                    };
                }
            };
        }}

    };
}

RT6502::QueuedInstr RT6502::InstructionSet::LDX(CPU& cpu) {
    return {
        {[&] {
            cpu.X = cpu.DataBus;
            cpu.PS.Z = cpu.X == 0;
            cpu.PS.N = cpu.X >> 7;
            return std::nullopt;
        }}
    };
}

/**
 *
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
RT6502::QueuedInstr RT6502::InstructionSet::LDA(CPU& cpu) {
    return {
        {[&] {
            cpu.A = cpu.DataBus;
            cpu.PS.Z = cpu.A == 0;
            cpu.PS.N = cpu.A >> 7;
            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::STA(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::TSX(CPU& cpu) {
    return {
        {[&] {
            cpu.X = cpu.SP;
            cpu.PS.Z = cpu.X == 0;
            cpu.PS.N = cpu.X >> 7;
            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::PHA(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::STX(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.X;
            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::CMP(CPU& cpu) {
    return {
        {[&] {
            cpu.PS.C = cpu.A >= cpu.DataBus;
            cpu.PS.Z = cpu.A == cpu.DataBus;
            cpu.PS.N = (cpu.A - cpu.DataBus) >> 7;

            return std::nullopt;
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::INC(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            return QueuedInstr{
                [&] {
                    cpu.RW = false;
                    cpu.DataBus += 1;
                    cpu.PS.Z = cpu.DataBus == 0;
                    cpu.PS.N = cpu.DataBus >> 7;
                    return std::nullopt;
                }
            };
        }}
    };
}

RT6502::QueuedInstr RT6502::InstructionSet::BEQ(CPU&) {
    return {
        [&] {
            return std::nullopt;
        }
    };
}