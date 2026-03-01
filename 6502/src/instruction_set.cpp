#include "6502/instruction_set.h"

/**
 *
 * @warning Ce n'est pas la bonne séquence d'exécution, mais on peut vivre avec
 */
std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::JSR(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.PC.High;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        }},
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.PC.Low;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        }},
        {[&] {
            cpu.PC = cpu.AddressRegister;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::JMP(CPU& cpu) {
    return {
        {[&] {
            cpu.PC = cpu.AddressBus;
        }}
    };
}

/**
 *
 * @warning Ce n'est pas la bonne séquence d'exécution, mais on peut vivre avec
 */
std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::RTS(CPU& cpu) {
    return {
        {[&] {
            cpu.SP++;
        }},
        {[&] {
            cpu.AddressBus.Low = cpu.SP++;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        }},
        {[&] {
            cpu.AddressRegister.Low = cpu.DataBus;
            cpu.AddressBus.Low = cpu.SP;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        }},
        {[&] {
            cpu.AddressRegister.High = cpu.DataBus;
        }},
        {[&] {
            cpu.PC = cpu.AddressRegister;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::LDX(CPU& cpu) {
    return {
        {[&] {
            cpu.X = cpu.DataBus;
            cpu.PS.Z = cpu.X == 0;
            cpu.PS.N = cpu.X >> 7;
        }}
    };
}

/**
 *
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::LDA(CPU& cpu) {
    return {
        {[&] {
            cpu.A = cpu.DataBus;
            cpu.PS.Z = cpu.A == 0;
            cpu.PS.N = cpu.A >> 7;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::STA(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::TSX(CPU& cpu) {
    return {
        {[&] {
            cpu.X = cpu.SP;
            cpu.PS.Z = cpu.X == 0;
            cpu.PS.N = cpu.X >> 7;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::PHA(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::STX(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
            cpu.DataBus = cpu.X;
        }}
    };
}

std::vector<RT6502::QueuedInstr> RT6502::InstructionSet::INC(CPU& cpu) {
    return {
        {[&] {
            cpu.RW = false;
        }},
        {[&] {
            cpu.RW = false;
            cpu.DataBus += 1;
            cpu.PS.Z = cpu.DataBus == 0;
            cpu.PS.N = cpu.DataBus >> 7;
        }}
    };
}