/**
 * Contient les types généraux qui sont utilisé pour la représentation du 6502.
 */

#pragma once

#include <cstdint>
#include <format>
#include <functional>

namespace RT6502 {
class CPU;

/**
 * Représentation de 8 bits sur un 6502.
 */
using Byte = uint8_t;

/**
 * Représentation de 16 bits sur un 6502.
 * Séparation entre 8 bits Low et 8 bits High.
 */
union Word {
    uint16_t Value;

    struct {
        Byte Low;
        Byte High;
    };

    constexpr Word(const int& val) : Value(val) {}
    constexpr Word(const Byte& high, const Byte& low) : Low(low), High(high) {}

    constexpr Word operator++(int) {
        const auto old = *this;
        operator++();
        return old;
    }

    constexpr Word& operator++() {
        ++Value;
        return *this;
    }

    constexpr Word operator--(int) {
        const auto old = *this;
        operator--();
        return old;
    }

    constexpr Word& operator--() {
        --Value;
        return *this;
    }

    constexpr void operator+=(const Byte rvalue) {
        Value += rvalue;
    }

    constexpr void operator+=(const int8_t rvalue) {
        Value += rvalue;
    }

    constexpr bool operator>=(const int rvalue) const {
        return Value >= rvalue;
    }

    operator uint16_t() const {
        return Value;
    }
};

/**
 * Représente les différents flags du Processor Status sur 8 bits.
 */
struct Flags {
    Byte C : 1;  // Bit 0 - Carry
    Byte Z : 1;  // Bit 1 - Zero Result
    Byte I : 1;  // Bit 2 - Interrupt Disable
    Byte D : 1;  // Bit 3 - Decimal mode
    Byte B : 1;  // Bit 4 - Break Command
    Byte _ : 1;  // Bit 5 - Expansion (Unused)
    Byte V : 1;  // Bit 6 - Overflow
    Byte N : 1;  // Bit 7 - Negative Result

    Flags() : C(0), Z(0), I(0), D(0), B(1), _(1), V(0), N(0) {
    }

    Flags(const Byte c, const Byte z, const Byte i, const Byte d, const Byte b, const Byte _, const Byte v, const Byte n) : C(c), Z(z), I(i), D(d), B(b), _(1), V(v), N(n) {
    }

    explicit operator Byte() const {
        return std::bit_cast<Byte>(*this);
    }

    void operator=(const Byte value) {
        *this = std::bit_cast<Flags, Byte>(value);
        _ = 1;  // S'assurer que le Bit reste allumé
    }

    bool operator==(const Flags& value) const {
        return static_cast<Byte>(*this) == static_cast<Byte>(value);
    }

    bool operator==(const Byte& value) const {
        return static_cast<Byte>(*this) == value;
    }
};

/**
 * Utilisé pour le mode d'adressage.
 * Permet de savoir si le mode d'adressage doit faire une lecture et/ou attendre pour faire une écriture.
 */
enum ReadWrite : Byte {
    Read = 1 << 0,
    Write = 1 << 1,
    RMW = Read | Write
};

/**
 * Nous permet d'avoir une fonction qui pointe vers la prochaine fonction à exécuter.
 * C'est utilisé pour définir chaque action par cycle.
 */
struct QueuedInstr {
    std::function<QueuedInstr(CPU&)> Func;

    template <typename T>
    QueuedInstr(const T& f) : Func(f) {}

    explicit QueuedInstr(const std::nullptr_t& f) : Func(nullptr) {}

    /**
     * Exécute la fonction actuel et retourne la prochaine fonction à exécuter.
     * @return La prochaine fonction à exécuter
     */
    QueuedInstr operator()(CPU& cpu) const {
        return Func(cpu);
    }

    bool has_value() const {
        return Func != nullptr;
    }
};

}  // namespace RT6502

/**
 * Nous permet de formatter le type Word comme un uint16_t.
 */
template <>
struct std::formatter<RT6502::Word> : std::formatter<uint16_t> {
    auto format(const RT6502::Word& id, std::format_context& ctx) const {
        return std::formatter<uint16_t>::format(id.Value, ctx);
    }
};
