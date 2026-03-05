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
enum Opcodes : Byte {

    INS_ASL_ZP = 0x06,
    INS_ASL_ABS = 0x0E,

    INS_JSR_ABS = 0x20,
    INS_JMP_ABS = 0x4C,
    INS_RTS_IMP = 0x60,

    INS_ADC_IMM = 0x69,
    INS_ADC_ZP = 0x65,
    INS_ADC_ABS = 0x6D,

    INS_LDY_IMM = 0xA0,
    INS_LDY_ZP = 0xA4,
    INS_LDY_ABS = 0xAC,
    INS_LDX_IMM = 0xA2,
    INS_LDX_ZP = 0xA6,
    INS_LDX_ABS = 0xAE,
    INS_LDA_IMM = 0xA9,
    INS_LDA_ZP = 0xA5,
    INS_LDA_ABS = 0xAD,

    INS_STY_ZP = 0x84,
    INS_STY_ABS = 0x8C,
    INS_STA_ZP = 0x85,
    INS_STA_ABS = 0x8D,
    INS_STX_ZP = 0x86,
    INS_STX_ABS = 0x8E,

    INS_TSX_IMP = 0xBA,
    INS_PHP_IMP = 0x08,
    INS_PLP_IMP = 0x28,
    INS_PHA_IMP = 0x48,
    INS_PLA_IMP = 0x68,

    INS_CMP_IMM = 0xC9,
    INS_CMP_ZP = 0xC5,
    INS_CMP_ABS = 0xCD,

    INS_INY_IMP = 0xC8,
    INS_INX_IMP = 0xE8,
    INS_INC_ZP = 0xE6,
    INS_INC_ABS = 0xEE,

    INS_BPL_REL = 0x10,
    INS_BMI_REL = 0x30,
    INS_BVC_REL = 0x50,
    INS_BVS_REL = 0x70,
    INS_BCC_REL = 0x90,
    INS_BCS_REL = 0xB0,
    INS_BNE_REL = 0xD0,
    INS_BEQ_REL = 0xF0,

};

struct Instruction {
    Opcodes Opcode;
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

QueuedInstr ASL(CPU&);
QueuedInstr JSR(CPU&);
QueuedInstr JMP(CPU&);
QueuedInstr RTS(CPU&);
QueuedInstr ADC(CPU&);
QueuedInstr LDY(CPU&);
QueuedInstr LDX(CPU&);
QueuedInstr LDA(CPU&);
QueuedInstr STY(CPU&);
QueuedInstr STX(CPU&);
QueuedInstr STA(CPU&);
QueuedInstr TSX(CPU&);
QueuedInstr PHP(CPU&);
QueuedInstr PLA(CPU&);
QueuedInstr PHA(CPU&);
QueuedInstr PLP(CPU&);
QueuedInstr CMP(CPU&);
QueuedInstr INY(CPU&);
QueuedInstr INX(CPU&);
QueuedInstr INC(CPU&);
QueuedInstr BPL(CPU&);
QueuedInstr BMI(CPU&);
QueuedInstr BVC(CPU&);
QueuedInstr BVS(CPU&);
QueuedInstr BCC(CPU&);
QueuedInstr BCS(CPU&);
QueuedInstr BNE(CPU&);
QueuedInstr BEQ(CPU&);

inline const std::map<Opcodes, const Instruction> OPCODE_LIST = {
    {INS_ASL_ZP, {INS_ASL_ZP, 2, 5, "ASL", AddressingMode::AddressingMode::Zeropage, Read, ASL}},
    {INS_ASL_ABS, {INS_ASL_ABS, 3, 6, "ASL", AddressingMode::AddressingMode::Absolute, Read, ASL}},
    {INS_JSR_ABS, {INS_JSR_ABS, 3, 6, "JSR", AddressingMode::AddressingMode::Absolute, Read, JSR}},
    {INS_JMP_ABS, {INS_JMP_ABS, 3, 3, "JMP", AddressingMode::AddressingMode::Absolute, Write, JMP}},
    {INS_RTS_IMP, {INS_RTS_IMP, 1, 6, "RTS", AddressingMode::AddressingMode::Implicit, Read, RTS}},
    {INS_ADC_IMM, {INS_ADC_IMM, 2, 2, "ADC", AddressingMode::AddressingMode::Immediate, Read, ADC}},
    {INS_ADC_ZP, {INS_ADC_ZP, 2, 3, "ADC", AddressingMode::AddressingMode::Zeropage, Read, ADC}},
    {INS_ADC_ABS, {INS_ADC_ABS, 3, 4, "ADC", AddressingMode::AddressingMode::Absolute, Read, ADC}},
    {INS_LDY_IMM, {INS_LDY_IMM, 2, 2, "LDY", AddressingMode::AddressingMode::Immediate, Read, LDY}},
    {INS_LDY_ZP, {INS_LDY_ZP, 2, 3, "LDY", AddressingMode::AddressingMode::Zeropage, Read, LDY}},
    {INS_LDY_ABS, {INS_LDY_ABS, 3, 4, "LDY", AddressingMode::AddressingMode::Absolute, Read, LDY}},
    {INS_LDX_IMM, {INS_LDX_IMM, 2, 2, "LDX", AddressingMode::AddressingMode::Immediate, Read, LDX}},
    {INS_LDX_ZP, {INS_LDX_ZP, 2, 3, "LDX", AddressingMode::AddressingMode::Zeropage, Read, LDX}},
    {INS_LDX_ABS, {INS_LDX_ABS, 3, 4, "LDX", AddressingMode::AddressingMode::Absolute, Read, LDX}},
    {INS_LDA_IMM, {INS_LDA_IMM, 2, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {INS_LDA_ZP, {INS_LDA_ZP, 2, 3, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {INS_LDA_ABS, {INS_LDA_ABS, 3, 4, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},
    {INS_STA_ZP, {INS_STA_ZP, 2, 3, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {INS_STA_ABS, {INS_STA_ABS, 3, 4, "STA", AddressingMode::AddressingMode::Absolute, Write, STA}},
    {INS_STY_ZP, {INS_STY_ZP, 2, 3, "STY", AddressingMode::AddressingMode::Zeropage, Write, STY}},
    {INS_STY_ABS, {INS_STY_ABS, 3, 4, "STY", AddressingMode::AddressingMode::Absolute, Write, STY}},
    {INS_STX_ZP, {INS_STX_ZP, 2, 3, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
    {INS_STX_ABS, {INS_STX_ABS, 3, 4, "STX", AddressingMode::AddressingMode::Absolute, Write, STX}},
    {INS_TSX_IMP, {INS_TSX_IMP, 1, 2, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},
    {INS_PHP_IMP, {INS_PHP_IMP, 1, 3, "PHP", AddressingMode::AddressingMode::Implicit, Write, PHP}},
    {INS_PLP_IMP, {INS_PLP_IMP, 1, 4, "PLP", AddressingMode::AddressingMode::Implicit, Read, PLP}},
    {INS_PHA_IMP, {INS_PHA_IMP, 1, 3, "PHA", AddressingMode::AddressingMode::Implicit, Write, PHA}},
    {INS_PLA_IMP, {INS_PLA_IMP, 1, 4, "PLA", AddressingMode::AddressingMode::Implicit, Read, PLA}},
    {INS_CMP_IMM, {INS_CMP_IMM, 2, 2, "CMP", AddressingMode::AddressingMode::Immediate, Read, CMP}},
    {INS_CMP_ZP, {INS_CMP_ZP, 2, 3, "CMP", AddressingMode::AddressingMode::Zeropage, Read, CMP}},
    {INS_CMP_ABS, {INS_CMP_ABS, 3, 4, "CMP", AddressingMode::AddressingMode::Absolute, Read, CMP}},
    {INS_INY_IMP, {INS_INY_IMP, 1, 2, "INY", AddressingMode::AddressingMode::Implicit, Read, INY}},
    {INS_INX_IMP, {INS_INX_IMP, 1, 2, "INX", AddressingMode::AddressingMode::Implicit, Read, INX}},
    {INS_INC_ZP, {INS_INC_ZP, 2, 5, "INC", AddressingMode::AddressingMode::Zeropage, Read, INC}},
    {INS_INC_ABS, {INS_INC_ABS, 3, 6, "INC", AddressingMode::AddressingMode::Absolute, Read, INC}},
    {INS_BPL_REL, {INS_BPL_REL, 2, 2, "BPL", AddressingMode::AddressingMode::Relative, Read, BPL}},
    {INS_BMI_REL, {INS_BMI_REL, 2, 2, "BMI", AddressingMode::AddressingMode::Relative, Read, BMI}},
    {INS_BVC_REL, {INS_BVC_REL, 2, 2, "BVC", AddressingMode::AddressingMode::Relative, Read, BVC}},
    {INS_BVS_REL, {INS_BVS_REL, 2, 2, "BVS", AddressingMode::AddressingMode::Relative, Read, BVS}},
    {INS_BCC_REL, {INS_BCC_REL, 2, 2, "BCC", AddressingMode::AddressingMode::Relative, Read, BCC}},
    {INS_BCS_REL, {INS_BCS_REL, 2, 2, "BCS", AddressingMode::AddressingMode::Relative, Read, BCS}},
    {INS_BNE_REL, {INS_BNE_REL, 2, 2, "BNE", AddressingMode::AddressingMode::Relative, Read, BNE}},
    {INS_BEQ_REL, {INS_BEQ_REL, 2, 2, "BEQ", AddressingMode::AddressingMode::Relative, Read, BEQ}},
};

}  // namespace RT6502::InstructionSet