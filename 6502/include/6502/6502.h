#pragma once

#include <optional>

#include "cpu.h"
#include "memory.h"

namespace RT6502 {
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
    std::optional<QueuedInstr> FonctionsToExecutes;

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
};

}  // namespace RT6502