#pragma once

#include <cstdint>

namespace RT6502 {

using Byte = uint8_t;
using Word = uint16_t;

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

}  // namespace RT6502
