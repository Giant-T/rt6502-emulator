#pragma once

#include <chrono>

#include "cpu.h"
#include "frequency.h"
#include "memory.h"

namespace RT6502 {
using namespace std::chrono;

/**
 * Instance d'un 6502 émulé.
 */
struct RT6502 {
    CPU Cpu;
    Memory Mem;
    /**
     * Le nombre de cycles total exécuté.
     */
    size_t CyclesCounter = 0;
    /**
     * La prochaine fonction à exécuter pour le prochain cycle.
     */
    QueuedInstr FonctionsToExecutes = nullptr;

    nanoseconds TotalCycleElapsedTime = nanoseconds::zero();

    Frequency Freq = 1.0_MHz;

    /**
     * Réinitialise le 6502 et le prépare à démarrer.
     * @param startAddress Adresse pour le PC
     */
    void Reset(const Word startAddress = 0x0000) noexcept;
    /**
     * Exécute une instruction au complet.
     */
    void Execute();
    /**
     * Exécute un cycle.
     */
    void ExecuteTick();

    /**
     * Charge dans la mémoire le contenu binaire d'un fichier.
     * @return Succès ou échec du chargement du fichier.
     */
    bool LoadFile(const char*);

    template <class T>
    T AverageCycleElapsedTime() const {
        return duration_cast<T>(TotalCycleElapsedTime / CyclesCounter);
    }
};

}  // namespace RT6502