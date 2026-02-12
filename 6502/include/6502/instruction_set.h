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

// opcodes
static constexpr Byte INS_LDA_IMM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;
static constexpr Byte INS_LDA_ABS = 0xAD;
static constexpr Byte INS_STA_ZP = 0x85;
static constexpr Byte INS_STX_ZP = 0x86;
static constexpr Byte INS_TSX_IMP = 0xBA;

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
    {INS_LDA_IMM, {INS_LDA_IMM, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {INS_LDA_ZP, {INS_LDA_ZP, 2, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {INS_LDA_ABS, {INS_LDA_ABS, 3, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},
    {INS_STA_ZP, {INS_STA_ZP, 2, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {INS_TSX_IMP, {INS_TSX_IMP, 1, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},
    //{0x48, {0x48, 1, "PHA", AddressingMode::AddressingMode::Implicit, PHA}},
    {INS_STX_ZP, {INS_STX_ZP, 1, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
};

}  // namespace RT6502::InstructionSet