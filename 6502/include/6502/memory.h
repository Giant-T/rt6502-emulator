#pragma once

#include "types.h"

namespace RT6502 {
/**
 * Représente l'unité de mémoire d'un 6502.
 */
class Memory {
   public:
    /**
     * Taille maximal de la mémoire pour le 6502.
     * 64 Kb
     */
    static constexpr uint32_t MAX_MEMORY = 1024 * 64;
    Byte Data[MAX_MEMORY];

    Memory();

    void Init() noexcept;

    void Read(const Word& addrBus, Byte& dataBus) const;
    void Write(const Word& addrBus, const Byte& dataBus);

    Byte operator[](const Word&) const;
    Byte& operator[](const Word&);
};

}  // namespace RT6502