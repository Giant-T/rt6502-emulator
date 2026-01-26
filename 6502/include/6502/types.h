#pragma once

#include <cstdint>

namespace rt6502 {

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

}  // namespace rt6502
