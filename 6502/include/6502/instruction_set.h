/**
 * Contient la liste des instructions CPU.
 *
 * @authors Nicolas Béland
 * @date 2026-01-23
 */

#pragma once

#include <functional>
#include <map>

#include "addressing_mode.h"
#include "cpu.h"
#include "types.h"

namespace RT6502::InstructionSet {

// opcodes
static constexpr Byte INS_JSR_ABS = 0x20;
static constexpr Byte INS_JMP_ABS = 0x4C;
static constexpr Byte INS_RTS_IMP = 0x60;
static constexpr Byte INS_LDX_IMM = 0xA2;
static constexpr Byte INS_LDX_ZP = 0xA6;
static constexpr Byte INS_LDX_ABS = 0xAE;
static constexpr Byte INS_LDA_IMM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;
static constexpr Byte INS_LDA_ABS = 0xAD;
static constexpr Byte INS_STA_ZP = 0x85;
static constexpr Byte INS_STA_ABS = 0x8D;
static constexpr Byte INS_STX_ZP = 0x86;
static constexpr Byte INS_STX_ABS = 0x8E;
static constexpr Byte INS_TSX_IMP = 0xBA;
static constexpr Byte INS_PHA_IMP = 0x48;
static constexpr Byte INS_CMP_IMM = 0xC9;
static constexpr Byte INS_CMP_ZP = 0xC5;
static constexpr Byte INS_CMP_ABS = 0xCD;
static constexpr Byte INS_INC_ZP = 0xE6;
static constexpr Byte INS_INC_ABS = 0xEE;
static constexpr Byte INS_BEQ_REL = 0xF0;

struct Instruction {
    Byte Opcode;
    Byte Bytes;
    Byte Cycles;
    std::string Name;
    AddressingMode::AddressingMode AddrMode;
    ReadWrite RW;
    std::function<QueuedInstr(CPU&)> Func;

    std::string Format() const noexcept {
        return AddressingMode::Format(AddrMode);
    }
};

QueuedInstr JSR(CPU&);
QueuedInstr JMP(CPU&);
QueuedInstr RTS(CPU&);
QueuedInstr LDX(CPU&);
QueuedInstr LDA(CPU&);
QueuedInstr STA(CPU&);
QueuedInstr TSX(CPU&);
QueuedInstr PHA(CPU&);
QueuedInstr STX(CPU&);
QueuedInstr CMP(CPU&);
QueuedInstr INC(CPU&);
QueuedInstr BEQ(CPU&);

inline const std::map<Byte, const Instruction> OPCODE_LIST = {
    {INS_JSR_ABS, {INS_JSR_ABS, 3, 6, "JSR", AddressingMode::AddressingMode::Absolute, Read, JSR}},
    {INS_JMP_ABS, {INS_JMP_ABS, 3, 3, "JMP", AddressingMode::AddressingMode::Absolute, Write, JMP}},
    {INS_RTS_IMP, {INS_RTS_IMP, 1, 6, "RTS", AddressingMode::AddressingMode::Implicit, Read, RTS}},
    {INS_LDX_IMM, {INS_LDX_IMM, 2, 2, "LDX", AddressingMode::AddressingMode::Immediate, Read, LDX}},
    {INS_LDX_ZP, {INS_LDX_ZP, 2, 3, "LDX", AddressingMode::AddressingMode::Zeropage, Read, LDX}},
    {INS_LDX_ABS, {INS_LDX_ABS, 3, 4, "LDX", AddressingMode::AddressingMode::Absolute, Read, LDX}},
    {INS_LDA_IMM, {INS_LDA_IMM, 2, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {INS_LDA_ZP, {INS_LDA_ZP, 2, 3, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {INS_LDA_ABS, {INS_LDA_ABS, 3, 4, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},
    {INS_STA_ZP, {INS_STA_ZP, 2, 3, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {INS_STA_ABS, {INS_STA_ABS, 3, 4, "STA", AddressingMode::AddressingMode::Absolute, Write, STA}},
    {INS_STX_ZP, {INS_STX_ZP, 2, 3, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
    {INS_STX_ABS, {INS_STX_ABS, 3, 4, "STX", AddressingMode::AddressingMode::Absolute, Write, STX}},
    {INS_TSX_IMP, {INS_TSX_IMP, 1, 2, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},
    {INS_PHA_IMP, {INS_PHA_IMP, 1, 3, "PHA", AddressingMode::AddressingMode::Implicit, Write, PHA}},
    {INS_CMP_IMM, {INS_CMP_IMM, 2, 2, "CMP", AddressingMode::AddressingMode::Immediate, Read, CMP}},
    {INS_CMP_ZP, {INS_CMP_ZP, 2, 3, "CMP", AddressingMode::AddressingMode::Zeropage, Read, CMP}},
    {INS_CMP_ABS, {INS_CMP_ABS, 3, 4, "CMP", AddressingMode::AddressingMode::Absolute, Read, CMP}},
    {INS_INC_ZP, {INS_INC_ZP, 2, 5, "INC", AddressingMode::AddressingMode::Zeropage, Read, INC}},
    {INS_INC_ABS, {INS_INC_ABS, 3, 6, "INC", AddressingMode::AddressingMode::Absolute, Read, INC}},
    {INS_BEQ_REL, {INS_BEQ_REL, 2, 2, "BEQ", AddressingMode::AddressingMode::Relative, Read, BEQ}},
};

}  // namespace RT6502::InstructionSet