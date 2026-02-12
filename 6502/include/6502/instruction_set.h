/**
 * Contient la liste des instructions CPU.
 *
 * @authors Nicolas Béland
 * @date 2026-01-23
 */

#pragma once

#include <map>

#include "addressing_mode.h"
#include "cpu.h"
#include "types.h"

namespace RT6502::InstructionSet {

struct Instruction {
    Byte Opcode;
    Byte Bytes;
    std::string Name;
    AddressingMode::AddressingMode AddrMode;
    ReadWrite RW;
    void (*Func)(CPU&);

    std::string Format() const noexcept {
        return AddressingMode::Format(AddrMode);
    }
};

void LDA(CPU&);
void STA(CPU&);
void TSX(CPU&);
// void PHA(CPU&, Memory&);
void STX(CPU&);

inline const std::map<Byte, const Instruction> OPCODE_LIST = {
    {0xA9, {0xA9, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {0xA5, {0xA5, 2, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {0xAD, {0xAD, 3, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},
    {0x85, {0x85, 2, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {0xBA, {0xBA, 1, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},
    //{0x48, {0x48, 1, "PHA", AddressingMode::AddressingMode::Implicit, PHA}},
    {0x86, {0x86, 1, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
};

}  // namespace RT6502::InstructionSet