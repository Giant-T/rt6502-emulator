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
    // Déterminer le nombre de cycle pour la prochaine instruction
    auto cycles = InstructionSet::OPCODE_LIST.at(Cpu.DataBus).Cycles;

    // Exécuter l'instruction le nombre de cycles prédit
    while (cycles-- > 0) {
        ExecuteTick();
    }
}

void RT6502::RT6502::ExecuteTick() {
    Cpu.RW = true;  // Remettre la ligne en Read par défaut

    if (Cpu.SYNC) {
        // Décoder la prochaine instruction
        Cpu.IR = &InstructionSet::OPCODE_LIST.at(Cpu.DataBus);

        // Récupérer l'opérande (c'est le mode d'adressage qui va gérer ça)
        FonctionsToExecutes.push_range(AddressingMode::Execute(Cpu));

        // Récupérer la liste des instructions à exécuter à chaque cycle
        FonctionsToExecutes.push_range(Cpu.IR->Func(Cpu));

        Cpu.SYNC = false;
    }

    // Exécuter l'instruction
    FonctionsToExecutes.front()();
    FonctionsToExecutes.pop();

    if (Cpu.RW) {
        Mem.Read(Cpu.AddressBus, Cpu.DataBus);
    } else {
        Mem.Write(Cpu.AddressBus, Cpu.DataBus);
    }
}
