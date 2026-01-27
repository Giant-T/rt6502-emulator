#include "6502/cpu.h"

#include "6502/decode.h"

rt6502::CPU::CPU() : PC(0), SP(stack_pointer_begin), A(0), X(0), Y(0), PS() {
}

/**
 * Écriture du Stack
 * @param memory
 * @param value
 */
void rt6502::CPU::stack_push(Memory& memory, const Byte value) {
    memory[SP--] = value;
}

/**
 * Lecture du Stack
 * @param memory
 * @return
 */
rt6502::Byte rt6502::CPU::stack_pull(Memory& memory) {
    return memory[SP++];
}

void rt6502::CPU::reset(Memory& memory) noexcept {
    // Source : https://www.pagetable.com/?p=410

    PC = reset_vector_addr;  // Adresse du Reset Vector

    // PC = l'adresse que contient le RESET VECTOR
    PC = decode::fetch_word(PC, memory);

    SP = 0xFD;  // TODO: Revalider
    PS = {};
    A = X = Y = 0;

    memory.init();  // TODO: Le déplacer ailleur, car n'est pas une opération normal du RESET
}

void rt6502::CPU::execute(Memory& memory) {
    // Récupérer l'instruction
    const auto inst = decode::fetch_instruction(PC, memory);

    // Récupérer dans la mémoire via le mode d'adressage
    const auto param = addressing_mode::execute(inst.addr_mode, PC, memory);

    // Exécuter l'instruction
    inst.func(param, *this, memory);
}