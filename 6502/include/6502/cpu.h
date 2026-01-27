#pragma once

#include "memory.h"
#include "types.h"

namespace rt6502 {

class CPU {
   public:
    Word PC;  // Program Counter
    Byte SP;  // Stack Pointer

    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y

    Flags PS;

    CPU();

    /**
     * @ref Procedure ["https://www.c64-wiki.com/wiki/Reset_(Process)"]
     */
    void reset(Memory&) noexcept;
};

}  // namespace rt6502
