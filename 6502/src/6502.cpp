#include "6502/6502.h"

#include "6502/decode.h"
#include "6502/instruction_set.h"

void RT6502::RT6502::Reset() noexcept {
    Cpu.Reset(Mem);

    // FIXME: Faire une première lecture mémoire pour le premier Fetch
    Cpu.AddressBus = Cpu.PC++;
    Mem.Read(Cpu.AddressBus, Cpu.DataBus);
}

/**
 * Ici, on va exécuter une instruction au complet
 * On suit la séquence d'exécution décrit ici: https://www.cpcwiki.eu/index.php/MOS_6502
 */
void RT6502::RT6502::Execute() {
    do {
        ExecuteTick();
        ++CyclesCounter;
    } while (FonctionsToExecutes.has_value());
}

void RT6502::RT6502::ExecuteTick() {
    Cpu.RW = true;  // Remettre la ligne en Read par défaut

    if (Cpu.SYNC) {
        // Décoder la prochaine instruction
        Cpu.IR = &InstructionSet::OPCODE_LIST.at(Cpu.DataBus);

        FonctionsToExecutes.emplace(AddressingMode::Execute(Cpu));

        Cpu.SYNC = false;
    }

    FonctionsToExecutes = FonctionsToExecutes.value()();

    // Gérer automatiquement le SYNC/Fetch à la fin de l'instruction
    if (!FonctionsToExecutes.has_value()) {
        if (Cpu.RW) {
            // Si c'est une lecture, alors on fait le Fetch
            Cpu.AddressBus = Cpu.PC++;
            Cpu.SYNC = true;
        } else {
            // Sinon, on rajoute un cycle
            FonctionsToExecutes.emplace([&] {
                // C'est vide, car sera traité par le IF juste au dessus
                // Cpu.AddressBus = Cpu.PC++;
                // Cpu.SYNC = true;
                return std::nullopt;
            });
        }
    }

    if (Cpu.RW) {
        Mem.Read(Cpu.AddressBus, Cpu.DataBus);
    } else {
        Mem.Write(Cpu.AddressBus, Cpu.DataBus);
    }
}
