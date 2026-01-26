#pragma once

#include "memory.h"
#include "types.h"

namespace rt6502 {
/**
 * @ref http://www.erich-foltyn.eu/Technique/6502.html
 */
class CPU {
   public:
    Word PC;  // Program Counter
    Byte SP;  // Stack Pointer

    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y

    Flags PS;  // Processor Status

    CPU();

    /**
     * @ref Procedure ["https://www.c64-wiki.com/wiki/Reset_(Process)"]
     */
    void reset(Memory&) noexcept;
    void execute(Memory&);
};

}  // namespace rt6502