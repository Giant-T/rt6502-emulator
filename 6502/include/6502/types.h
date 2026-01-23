#pragma once

#include <cstdint>

namespace rt6502 {

using Byte = uint8_t;
using Word = uint16_t;

struct Flags {
    Byte C : 1;  // Carry
    Byte Z : 1;  // Zero
    Byte I : 1;  // Interrupt Disable
    Byte D : 1;  // Decimal mode
    Byte B : 1;  // Break Command
    Byte O : 1;  // Overflow
    Byte N : 1;  // Negative
};

}  // namespace rt6502
