#pragma once

#include "memory.h"
#include "types.h"

namespace RT6502 {
/**
 * @ref http://www.erich-foltyn.eu/Technique/6502.html
 */
class CPU {
   public:
    static constexpr Byte STACK_POINTER_BEGIN = 0xFF;
    static constexpr Word NMI_VECTOR_ADDR = 0xFFFA;
    static constexpr Word RESET_VECTOR_ADDR = 0xFFFC;
    static constexpr Word IRQBRK_VECTOR_ADDR = 0xFFFE;

    Word PC;  // Program Counter
    Byte SP;  // Stack Pointer

    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y

    Flags PS;  // Processor Status

    CPU();

    void StackPush(Memory&, Byte);
    Byte StackPull(Memory&);

    /**
     * @ref Procedure ["https://www.c64-wiki.com/wiki/Reset_(Process)"]
     */
    void Reset(Memory&) noexcept;
    void Execute(Memory&);
};

}  // namespace RT6502