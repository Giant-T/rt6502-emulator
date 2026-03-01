#pragma once

#include <cstdint>
#include <format>
#include <functional>

namespace RT6502 {

using Byte = uint8_t;
// using Word = uint16_t;

using InstrFuncPtr = std::function<void()>;

union Word {
    uint16_t Value;

    struct {
        Byte Low;
        Byte High;
    };

    constexpr Word(const int& val) : Value(val) {}

    constexpr Word operator++(int) {
        const auto old = *this;
        operator++();
        return old;
    }

    constexpr Word& operator++() {
        ++Value;
        return *this;
    }

    operator uint16_t() const {
        return Value;
    }
};

struct Flags {
    Byte C : 1;  // Bit 0 - Carry
    Byte Z : 1;  // Bit 1 - Zero Result
    Byte I : 1;  // Bit 2 - Interrupt Disable
    Byte D : 1;  // Bit 3 - Decimal mode
    Byte B : 1;  // Bit 4 - Break Command
    Byte _ : 1;  // Bit 5 - Expansion (Unused)
    Byte V : 1;  // Bit 6 - Overflow
    Byte N : 1;  // Bit 7 - Negative Result
};

enum TimeStates {
    T0 = 0,
    T1 = 1,
    T2 = 2,
    T3 = 3,
    T4 = 4,
    T5 = 5
};

enum ReadWrite {
    Read = 1 << 0,
    Write = 1 << 1,
    RMW = Read | Write
};

struct QueuedInstr {
    InstrFuncPtr Func;
    bool RunNext;

    QueuedInstr(const InstrFuncPtr& func, const bool runNext = false) : Func(func), RunNext(runNext) {}
};

}  // namespace RT6502

template <>
struct std::formatter<RT6502::Word> : std::formatter<uint16_t> {
    auto format(const RT6502::Word& id, std::format_context& ctx) const {
        return std::formatter<uint16_t>::format(id.Value, ctx);
    }
};
