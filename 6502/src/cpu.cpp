#include "6502/cpu.h"

#include "6502/decode.h"

RT6502::CPU::CPU() : PC(0), SP(STACK_POINTER_BEGIN), A(0), X(0), Y(0), PS() {
}

/**
 * Écriture du Stack
 * @param memory
 * @param value
 */
void RT6502::CPU::StackPush(Memory& memory, const Byte value) {
    memory[SP--] = value;
}

/**
 * Lecture du Stack
 * @param memory
 * @return
 */
RT6502::Byte RT6502::CPU::StackPull(Memory& memory) {
    return memory[SP++];
}

void RT6502::CPU::Reset(Memory& memory) noexcept {
    // Source : https://www.pagetable.com/?p=410

    PC = RESET_VECTOR_ADDR;  // Adresse du Reset Vector

    // PC = l'adresse que contient le RESET VECTOR
    PC = Decode::FetchWord(PC, memory);

    SP = 0xFD;  // TODO: Revalider
    PS = {};
    A = X = Y = 0;

    memory.Init();  // TODO: Le déplacer ailleur, car n'est pas une opération normal du RESET
}

void RT6502::CPU::Execute(Memory& memory) {
    // Récupérer l'instruction
    const auto inst = Decode::FetchInstruction(PC, memory);

    // Récupérer dans la mémoire via le mode d'adressage
    const auto param = AddressingMode::Execute(inst.AddrMode, PC, memory);

    // Exécuter l'instruction
    inst.Func(param, *this, memory);
}