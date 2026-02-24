#include "6502/instruction_set.h"

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::JSR(CPU&) {
    return {};
}

/**
 *
 * @param cpu
 * @ref source [http://www.6502.org/users/obelisk/6502/reference.html#LDA]
 */
std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::LDA(CPU& cpu) {
    return {
        [&] {
            cpu.A = cpu.DataBus;
            cpu.PS.Z = cpu.A == 0;
            cpu.PS.N = cpu.A >> 7;

            // Faire un fetch de l'op
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        }
    };
}

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::STA(CPU& cpu) {
    return {
        [&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
        },
        [&] {
            // Faire un fetch de l'op
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        }
    };
}

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::TSX(CPU& cpu) {
    return {
        [&] {

        },
        [&] {
            cpu.X = cpu.SP;
            cpu.PS.Z = cpu.X == 0;
            cpu.PS.N = cpu.X >> 7;

            // Faire un fetch de l'op
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        },
    };
}

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::PHA(CPU& cpu) {
    return {
        [&] {
            // TODO: Voir c'est quoi qui se passe à cette étape normalement...
            // En ce moment c'est juste un dummy read
        },
        [&] {
            cpu.RW = false;
            cpu.DataBus = cpu.A;
            cpu.AddressBus.Low = cpu.SP--;
            cpu.AddressBus.High = CPU::STACK_POINTER_PAGE;
        },
        [&] {
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        }
    };
}

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::STX(CPU& cpu) {
    return {
        [&] {
            cpu.RW = false;
            cpu.DataBus = cpu.X;
        },
        [&] {
            // Faire un fetch de l'op
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        }
    };
}

std::vector<RT6502::InstrFuncPtr> RT6502::InstructionSet::INC(CPU& cpu) {
    return {
        [&] {
            cpu.RW = false;
        },
        [&] {
            cpu.RW = false;
            cpu.DataBus += 1;
            cpu.PS.Z = cpu.DataBus == 0;
            cpu.PS.N = cpu.DataBus >> 7;
        },
        [&] {
            // Faire un fetch de l'op
            cpu.AddressBus = cpu.PC++;
            cpu.SYNC = true;
        }
    };
}