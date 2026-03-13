#pragma once

#include "memory.h"
#include "types.h"

namespace RT6502::InstructionSet {
struct Instruction;
}

namespace RT6502 {
/**
 * @ref http://www.erich-foltyn.eu/Technique/6502.html
 */
class CPU {
   public:
    static constexpr Byte STACK_POINTER_PAGE = 0x01;
    static constexpr Byte STACK_POINTER_BEGIN = 0xFF;
    static constexpr Word STACK_POINTER_ADDRESS = 0x01FF;
    static constexpr Word NMI_VECTOR_ADDR = 0xFFFA;
    static constexpr Word RESET_VECTOR_ADDR = 0xFFFC;
    static constexpr Word IRQBRK_VECTOR_ADDR = 0xFFFE;

    Word PC;  // Program Counter
    Byte SP;  // Stack Pointer

    Byte A;  // Accumulator
    Byte X;  // Index Register X
    Byte Y;  // Index Register Y

    Flags PS;  // Processor Status

    bool RW;    // Read or Write on memory. Read = 1, Write = 0; C'est la direction du transfert de données entre le processeur et les chips.
    bool SYNC;  // 1 = OPCODE Fetch, 0 = no fetch

    Byte DataBus;                           // All instructions and data transfers between the processor and memory take place on these lines. Page 47
    Word AddressBus;                        // Also Address Register. Est utilisé pour accéder à la mémoire
    Word AddressRegister;                   // Contient ADL et ADH;
    const InstructionSet::Instruction* IR;  // Instruction Register. Holds the fetched instruction opcode byte while the CPU decodes and executes it.

    TimeStates CurrentState = T0;

    CPU();

    /**
     * @ref Procedure ["https://www.c64-wiki.com/wiki/Reset_(Process)"]
     */
    void Reset(Memory&) noexcept;
};

}  // namespace RT6502
