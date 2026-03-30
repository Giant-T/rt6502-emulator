#include "6502/6502.h"

#include <fstream>

#include "6502/decode.h"
#include "6502/instruction_set.h"

void RT6502::RT6502::Reset(const Word startAddress) noexcept {
    Cpu.Reset(Mem);

    CyclesCounter = 0;
    CycleElapsedTime = nanoseconds::zero();
    TotalCycleElapsedTime = nanoseconds::zero();

    // FIXME: Faire une première lecture mémoire pour le premier Fetch
    Cpu.PC = startAddress;
    Cpu.AddressBus = Cpu.PC++;
    Mem.Read(Cpu.AddressBus, Cpu.DataBus);
}

void RT6502::RT6502::Execute() {
    do {
        ExecuteCycle();

        time_point<steady_clock> cycleEndTime = high_resolution_clock::now();

        // Attendre que sa fasse assez longtemps depuis l'exécution du cycle précédent
        while (cycleEndTime < CycleLastEndTime + Freq.CycleDuration()) {
            cycleEndTime = high_resolution_clock::now();
        }

        ++CyclesCounter;
        CycleElapsedTime = cycleEndTime - CycleLastEndTime;
        TotalCycleElapsedTime += CycleElapsedTime;

        CycleLastEndTime = cycleEndTime;
    } while (FonctionsToExecutes.has_value());
}

void RT6502::RT6502::ExecuteCycle() {
    Cpu.RW = true;  // Remettre la ligne en Read par défaut

    if (Cpu.SYNC) {
        // Décoder la prochaine instruction
        Cpu.IR = &InstructionSet::OPCODE_LIST.at(static_cast<InstructionSet::Opcodes>(Cpu.DataBus));

        FonctionsToExecutes = Cpu.IR->AddrMode;

        Cpu.SYNC = false;
    }

    FonctionsToExecutes = FonctionsToExecutes.Func(Cpu);

    // Gérer automatiquement le SYNC/Fetch à la fin de l'instruction
    if (!FonctionsToExecutes.has_value()) {
        if (Cpu.RW) {
            // Si c'est une lecture, alors on fait le Fetch
            Cpu.AddressBus = Cpu.PC++;
            Cpu.SYNC = true;
        } else {
            // Sinon, on rajoute un cycle
            FonctionsToExecutes = [](CPU&) -> QueuedInstr {
                // C'est vide, car sera traité par le IF juste au dessus
                return nullptr;
            };
        }
    }

    if (Cpu.RW) {
        Mem.Read(Cpu.AddressBus, Cpu.DataBus);
    } else {
        Mem.Write(Cpu.AddressBus, Cpu.DataBus);
    }
}

bool RT6502::RT6502::LoadFile(const char* filepath) {
    std::ifstream file(filepath, std::ios::binary | std::ios::in);

    if (file.fail()) {
        return false;
    }

    file.read(reinterpret_cast<char*>(Mem.Data), Memory::MAX_MEMORY);

    return true;
}
