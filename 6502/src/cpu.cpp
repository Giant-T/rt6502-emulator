#include "6502/cpu.h"

#include "6502/decode.h"

RT6502::CPU::CPU() : PC(0), SP(STACK_POINTER_BEGIN), A(0), X(0), Y(0), RW(true), SYNC(true), DataBus(0), AddressBus(0), AddressRegister(0), IR(nullptr) {
}

void RT6502::CPU::Reset(Memory& memory) noexcept {
    // Source : https://www.pagetable.com/?p=410

    PC = RESET_VECTOR_ADDR;  // Adresse du Reset Vector

    // PC = l'adresse que contient le RESET VECTOR
    PC = Decode::FetchWord(PC, memory);

    SP = STACK_POINTER_BEGIN;  // TODO: Revalider
    PS = Flags();
    A = X = Y = 0;
}
