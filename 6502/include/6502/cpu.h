#pragma once

#include "memory.h"
#include "types.h"

namespace rt6502 {
/**
 * @ref http://www.erich-foltyn.eu/Technique/6502.html
 */
class CPU {
   public:
    static constexpr Byte stack_pointer_begin = 0xFF;
    static constexpr Word nmi_vector_addr = 0xFFFA; 
    static constexpr Word reset_vector_addr = 0xFFFC; 
    static constexpr Word irqbrk_vector_addr = 0xFFFE; 

    Word PC;  // Program Counter
    Byte SP;  // Stack Pointer

    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y

    Flags PS;  // Processor Status

    CPU();

    void stack_push(Memory&, Byte);
    Byte stack_pull(Memory&);

    /**
     * @ref Procedure ["https://www.c64-wiki.com/wiki/Reset_(Process)"]
     */
    void reset(Memory&) noexcept;
    void execute(Memory&);
};

}  // namespace rt6502