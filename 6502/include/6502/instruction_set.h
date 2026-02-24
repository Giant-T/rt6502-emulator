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
static constexpr Byte INS_LDA_IMM = 0xA9;
static constexpr Byte INS_LDA_ZP = 0xA5;
static constexpr Byte INS_LDA_ABS = 0xAD;
static constexpr Byte INS_STA_ZP = 0x85;
static constexpr Byte INS_STX_ZP = 0x86;
static constexpr Byte INS_TSX_IMP = 0xBA;
static constexpr Byte INS_PHA_IMP = 0x48;
static constexpr Byte INS_JSR_ABS = 0x20;
static constexpr Byte INS_INC_ZP = 0xE6;
static constexpr Byte INS_INC_ABS = 0xEE;

struct Instruction {
    Byte Opcode;
    Byte Bytes;
    std::string Name;
    AddressingMode::AddressingMode AddrMode;
    ReadWrite RW;
    std::function<std::vector<InstrFuncPtr>(CPU&)> Func;
    // void (*Func)(CPU&);

    std::string Format() const noexcept {
        return AddressingMode::Format(AddrMode);
    }
};

std::vector<InstrFuncPtr> JSR(CPU&);
std::vector<InstrFuncPtr> LDA(CPU&);
std::vector<InstrFuncPtr> STA(CPU&);
std::vector<InstrFuncPtr> TSX(CPU&);
std::vector<InstrFuncPtr> PHA(CPU&);
std::vector<InstrFuncPtr> STX(CPU&);
std::vector<InstrFuncPtr> INC(CPU&);

inline const std::map<Byte, const Instruction> OPCODE_LIST = {
    {INS_JSR_ABS, {INS_JSR_ABS, 3, "JSR", AddressingMode::AddressingMode::Absolute, Read, JSR}},
    {INS_LDA_IMM, {INS_LDA_IMM, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {INS_LDA_ZP, {INS_LDA_ZP, 2, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {INS_LDA_ABS, {INS_LDA_ABS, 3, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},
    {INS_STA_ZP, {INS_STA_ZP, 2, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {INS_TSX_IMP, {INS_TSX_IMP, 1, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},
    {INS_PHA_IMP, {INS_PHA_IMP, 1, "PHA", AddressingMode::AddressingMode::Implicit, Write, PHA}},
    {INS_STX_ZP, {INS_STX_ZP, 1, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
    {INS_INC_ZP, {INS_INC_ZP, 2, "INC", AddressingMode::AddressingMode::Zeropage, RMW, INC}},
    {INS_INC_ABS, {INS_INC_ABS, 3, "INC", AddressingMode::AddressingMode::Absolute, RMW, INC}},
};

}  // namespace RT6502::InstructionSet