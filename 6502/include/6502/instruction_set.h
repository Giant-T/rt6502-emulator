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

    INS_BRK_IMP = 0X00,

    // Set Flags
    INS_CLC_IMP = 0x18,
    INS_SEC_IMP = 0x38,
    INS_CLI_IMP = 0x58,
    INS_SEI_IMP = 0x78,
    INS_CLD_IMP = 0xD8,
    INS_SED_IMP = 0xF8,
    INS_CLV_IMP = 0xB8,

    // Arithmetic
    INS_ASL_ACC = 0x0A,
    INS_ASL_ZP = 0x06,
    INS_ASL_ABS = 0x0E,
    INS_LSR_ACC = 0x4A,
    INS_LSR_ZP = 0x46,
    INS_LSR_ABS = 0x4E,

    INS_BIT_ZP = 0x24,
    INS_BIT_ABS = 0x2C,

    INS_ROL_ACC = 0x2A,
    INS_ROL_ZP = 0x26,
    INS_ROL_ABS = 0x2E,
    INS_ROR_ACC = 0x6A,
    INS_ROR_ZP = 0x66,
    INS_ROR_ABS = 0x6E,

    INS_ADC_IMM = 0x69,
    INS_ADC_ZP = 0x65,
    INS_ADC_ABS = 0x6D,
    INS_SBC_IMM = 0xE9,
    INS_SBC_ZP = 0xE5,
    INS_SBC_ABS = 0xED,

    INS_ORA_IMM = 0x09,
    INS_ORA_ZP = 0x05,
    INS_ORA_ABS = 0x0D,
    INS_AND_IMM = 0x29,
    INS_AND_ZP = 0x25,
    INS_AND_ABS = 0x2D,
    INS_EOR_IMM = 0x49,
    INS_EOR_ZP = 0x45,
    INS_EOR_ABS = 0x4D,

    // Jump
    INS_JSR_ABS = 0x20,
    INS_JMP_ABS = 0x4C,
    INS_RTI_IMP = 0x40,
    INS_RTS_IMP = 0x60,

    // Load
    INS_LDY_IMM = 0xA0,
    INS_LDY_ZP = 0xA4,
    INS_LDY_ABS = 0xAC,
    INS_LDX_IMM = 0xA2,
    INS_LDX_ZP = 0xA6,
    INS_LDX_ABS = 0xAE,
    INS_LDA_IMM = 0xA9,
    INS_LDA_ZP = 0xA5,
    INS_LDA_ABS = 0xAD,

    // Store
    INS_STY_ZP = 0x84,
    INS_STY_ABS = 0x8C,
    INS_STA_ZP = 0x85,
    INS_STA_ABS = 0x8D,
    INS_STX_ZP = 0x86,
    INS_STX_ABS = 0x8E,

    // Stack
    INS_PHP_IMP = 0x08,
    INS_PLP_IMP = 0x28,
    INS_PHA_IMP = 0x48,
    INS_PLA_IMP = 0x68,

    // Transfer
    INS_TXA_IMP = 0x8A,
    INS_TYA_IMP = 0x98,
    INS_TXS_IMP = 0x9A,
    INS_TAY_IMP = 0xA8,
    INS_TAX_IMP = 0xAA,
    INS_TSX_IMP = 0xBA,

    // Compare
    INS_CPY_IMM = 0xC0,
    INS_CPY_ZP = 0xC4,
    INS_CPY_ABS = 0xCC,
    INS_CMP_IMM = 0xC9,
    INS_CMP_ZP = 0xC5,
    INS_CMP_ABS = 0xCD,
    INS_CPX_IMM = 0xE0,
    INS_CPX_ZP = 0xE4,
    INS_CPX_ABS = 0xEC,

    // Decrement
    INS_DEY_IMP = 0x88,
    INS_DEX_IMP = 0xCA,
    INS_DEC_ZP = 0xC6,
    INS_DEC_ABS = 0xCE,

    // Increment
    INS_INY_IMP = 0xC8,
    INS_INX_IMP = 0xE8,
    INS_INC_ZP = 0xE6,
    INS_INC_ABS = 0xEE,

    // Branching
    INS_BPL_REL = 0x10,
    INS_BMI_REL = 0x30,
    INS_BVC_REL = 0x50,
    INS_BVS_REL = 0x70,
    INS_BCC_REL = 0x90,
    INS_BCS_REL = 0xB0,
    INS_BNE_REL = 0xD0,
    INS_BEQ_REL = 0xF0,

    INS_NOP_IMP = 0xEA,

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

QueuedInstr BRK(CPU&);

// Flags
QueuedInstr CLC(CPU&);
QueuedInstr SEC(CPU&);
QueuedInstr CLI(CPU&);
QueuedInstr SEI(CPU&);
QueuedInstr CLD(CPU&);
QueuedInstr SED(CPU&);
QueuedInstr CLV(CPU&);

// Arithmetic
QueuedInstr ASL(CPU&);
QueuedInstr ASL_ACC(CPU&);
QueuedInstr LSR(CPU&);
QueuedInstr LSR_ACC(CPU&);

QueuedInstr ADC(CPU&);
QueuedInstr SBC(CPU&);

QueuedInstr BIT(CPU&);

QueuedInstr ROL(CPU&);
QueuedInstr ROL_ACC(CPU&);
QueuedInstr ROR(CPU&);
QueuedInstr ROR_ACC(CPU&);

QueuedInstr ORA(CPU&);
QueuedInstr AND(CPU&);
QueuedInstr EOR(CPU&);

// Jump
QueuedInstr JSR(CPU&);
QueuedInstr JMP(CPU&);
QueuedInstr RTI(CPU&);
QueuedInstr RTS(CPU&);

// Load
QueuedInstr LDY(CPU&);
QueuedInstr LDX(CPU&);
QueuedInstr LDA(CPU&);

// Store
QueuedInstr STY(CPU&);
QueuedInstr STX(CPU&);
QueuedInstr STA(CPU&);

// Stack
QueuedInstr PHP(CPU&);
QueuedInstr PLA(CPU&);
QueuedInstr PHA(CPU&);
QueuedInstr PLP(CPU&);

// Transfer
QueuedInstr TXA(CPU&);
QueuedInstr TYA(CPU&);
QueuedInstr TXS(CPU&);
QueuedInstr TAY(CPU&);
QueuedInstr TAX(CPU&);
QueuedInstr TSX(CPU&);

// Compare
QueuedInstr CPY(CPU&);
QueuedInstr CMP(CPU&);
QueuedInstr CPX(CPU&);

// Decrement
QueuedInstr DEY(CPU&);
QueuedInstr DEX(CPU&);
QueuedInstr DEC(CPU&);

// Increment
QueuedInstr INY(CPU&);
QueuedInstr INX(CPU&);
QueuedInstr INC(CPU&);

// Branching
QueuedInstr BPL(CPU&);
QueuedInstr BMI(CPU&);
QueuedInstr BVC(CPU&);
QueuedInstr BVS(CPU&);
QueuedInstr BCC(CPU&);
QueuedInstr BCS(CPU&);
QueuedInstr BNE(CPU&);
QueuedInstr BEQ(CPU&);

QueuedInstr NOP(CPU&);

inline const std::map<Opcodes, const Instruction> OPCODE_LIST = {
    {INS_BRK_IMP, {INS_BRK_IMP, 1, 7, "BRK", AddressingMode::AddressingMode::Implicit, Read, BRK}},

    // Flags
    {INS_CLC_IMP, {INS_CLC_IMP, 1, 2, "CLC", AddressingMode::AddressingMode::Implicit, Read, CLC}},
    {INS_SEC_IMP, {INS_SEC_IMP, 1, 2, "SEC", AddressingMode::AddressingMode::Implicit, Read, SEC}},
    {INS_CLI_IMP, {INS_CLI_IMP, 1, 2, "CLI", AddressingMode::AddressingMode::Implicit, Read, CLI}},
    {INS_SEI_IMP, {INS_SEI_IMP, 1, 2, "SEI", AddressingMode::AddressingMode::Implicit, Read, SEI}},
    {INS_CLD_IMP, {INS_CLD_IMP, 1, 2, "CLD", AddressingMode::AddressingMode::Implicit, Read, CLD}},
    {INS_SED_IMP, {INS_SED_IMP, 1, 2, "SED", AddressingMode::AddressingMode::Implicit, Read, SED}},
    {INS_CLV_IMP, {INS_CLV_IMP, 1, 2, "CLV", AddressingMode::AddressingMode::Implicit, Read, CLV}},

    // Arithmetic
    {INS_ASL_ACC, {INS_ASL_ACC, 1, 2, "ASL", AddressingMode::AddressingMode::Accumulator, Read, ASL_ACC}},
    {INS_ASL_ZP, {INS_ASL_ZP, 2, 5, "ASL", AddressingMode::AddressingMode::Zeropage, Read, ASL}},
    {INS_ASL_ABS, {INS_ASL_ABS, 3, 6, "ASL", AddressingMode::AddressingMode::Absolute, Read, ASL}},
    {INS_LSR_ACC, {INS_LSR_ACC, 1, 2, "LSR", AddressingMode::AddressingMode::Accumulator, Read, LSR_ACC}},
    {INS_LSR_ZP, {INS_LSR_ZP, 2, 5, "LSR", AddressingMode::AddressingMode::Zeropage, Read, LSR}},
    {INS_LSR_ABS, {INS_LSR_ABS, 3, 6, "LSR", AddressingMode::AddressingMode::Absolute, Read, LSR}},

    {INS_ADC_IMM, {INS_ADC_IMM, 2, 2, "ADC", AddressingMode::AddressingMode::Immediate, Read, ADC}},
    {INS_ADC_ZP, {INS_ADC_ZP, 2, 3, "ADC", AddressingMode::AddressingMode::Zeropage, Read, ADC}},
    {INS_ADC_ABS, {INS_ADC_ABS, 3, 4, "ADC", AddressingMode::AddressingMode::Absolute, Read, ADC}},
    {INS_SBC_IMM, {INS_SBC_IMM, 2, 2, "SBC", AddressingMode::AddressingMode::Immediate, Read, SBC}},
    {INS_SBC_ZP, {INS_SBC_ZP, 2, 3, "SBC", AddressingMode::AddressingMode::Zeropage, Read, SBC}},
    {INS_SBC_ABS, {INS_SBC_ABS, 3, 4, "SBC", AddressingMode::AddressingMode::Absolute, Read, SBC}},

    {INS_BIT_ZP, {INS_BIT_ZP, 2, 3, "BIT", AddressingMode::AddressingMode::Zeropage, Read, BIT}},
    {INS_BIT_ABS, {INS_BIT_ABS, 3, 4, "BIT", AddressingMode::AddressingMode::Absolute, Read, BIT}},

    {INS_ROL_ACC, {INS_ROL_ACC, 1, 2, "ROL", AddressingMode::AddressingMode::Accumulator, Read, ROL_ACC}},
    {INS_ROL_ZP, {INS_ROL_ZP, 2, 5, "ROL", AddressingMode::AddressingMode::Zeropage, Read, ROL}},
    {INS_ROL_ABS, {INS_ROL_ZP, 3, 6, "ROL", AddressingMode::AddressingMode::Absolute, Read, ROL}},
    {INS_ROR_ACC, {INS_ROR_ACC, 1, 2, "ROR", AddressingMode::AddressingMode::Accumulator, Read, ROR_ACC}},
    {INS_ROR_ZP, {INS_ROR_ZP, 2, 5, "ROR", AddressingMode::AddressingMode::Zeropage, Read, ROR}},
    {INS_ROR_ABS, {INS_ROR_ZP, 3, 6, "ROR", AddressingMode::AddressingMode::Absolute, Read, ROR}},

    {INS_ORA_IMM, {INS_ORA_IMM, 2, 2, "ORA", AddressingMode::AddressingMode::Immediate, Read, ORA}},
    {INS_ORA_ZP, {INS_ORA_ZP, 2, 3, "ORA", AddressingMode::AddressingMode::Zeropage, Read, ORA}},
    {INS_ORA_ABS, {INS_ORA_ABS, 3, 4, "ORA", AddressingMode::AddressingMode::Absolute, Read, ORA}},
    {INS_AND_IMM, {INS_AND_IMM, 2, 2, "AND", AddressingMode::AddressingMode::Immediate, Read, AND}},
    {INS_AND_ZP, {INS_AND_ZP, 2, 3, "AND", AddressingMode::AddressingMode::Zeropage, Read, AND}},
    {INS_AND_ABS, {INS_AND_ABS, 3, 4, "AND", AddressingMode::AddressingMode::Absolute, Read, AND}},
    {INS_EOR_IMM, {INS_EOR_IMM, 2, 2, "EOR", AddressingMode::AddressingMode::Immediate, Read, EOR}},
    {INS_EOR_ZP, {INS_EOR_ZP, 2, 3, "EOR", AddressingMode::AddressingMode::Zeropage, Read, EOR}},
    {INS_EOR_ABS, {INS_EOR_ABS, 3, 4, "EOR", AddressingMode::AddressingMode::Absolute, Read, EOR}},

    // Jump
    {INS_JSR_ABS, {INS_JSR_ABS, 3, 6, "JSR", AddressingMode::AddressingMode::Absolute, Read, JSR}},
    {INS_JMP_ABS, {INS_JMP_ABS, 3, 3, "JMP", AddressingMode::AddressingMode::Absolute, Write, JMP}},
    {INS_RTI_IMP, {INS_RTI_IMP, 1, 6, "RTI", AddressingMode::AddressingMode::Implicit, Read, RTI}},
    {INS_RTS_IMP, {INS_RTS_IMP, 1, 6, "RTS", AddressingMode::AddressingMode::Implicit, Read, RTS}},

    // Load
    {INS_LDY_IMM, {INS_LDY_IMM, 2, 2, "LDY", AddressingMode::AddressingMode::Immediate, Read, LDY}},
    {INS_LDY_ZP, {INS_LDY_ZP, 2, 3, "LDY", AddressingMode::AddressingMode::Zeropage, Read, LDY}},
    {INS_LDY_ABS, {INS_LDY_ABS, 3, 4, "LDY", AddressingMode::AddressingMode::Absolute, Read, LDY}},
    {INS_LDX_IMM, {INS_LDX_IMM, 2, 2, "LDX", AddressingMode::AddressingMode::Immediate, Read, LDX}},
    {INS_LDX_ZP, {INS_LDX_ZP, 2, 3, "LDX", AddressingMode::AddressingMode::Zeropage, Read, LDX}},
    {INS_LDX_ABS, {INS_LDX_ABS, 3, 4, "LDX", AddressingMode::AddressingMode::Absolute, Read, LDX}},
    {INS_LDA_IMM, {INS_LDA_IMM, 2, 2, "LDA", AddressingMode::AddressingMode::Immediate, Read, LDA}},
    {INS_LDA_ZP, {INS_LDA_ZP, 2, 3, "LDA", AddressingMode::AddressingMode::Zeropage, Read, LDA}},
    {INS_LDA_ABS, {INS_LDA_ABS, 3, 4, "LDA", AddressingMode::AddressingMode::Absolute, Read, LDA}},

    // Store
    {INS_STA_ZP, {INS_STA_ZP, 2, 3, "STA", AddressingMode::AddressingMode::Zeropage, Write, STA}},
    {INS_STA_ABS, {INS_STA_ABS, 3, 4, "STA", AddressingMode::AddressingMode::Absolute, Write, STA}},
    {INS_STY_ZP, {INS_STY_ZP, 2, 3, "STY", AddressingMode::AddressingMode::Zeropage, Write, STY}},
    {INS_STY_ABS, {INS_STY_ABS, 3, 4, "STY", AddressingMode::AddressingMode::Absolute, Write, STY}},
    {INS_STX_ZP, {INS_STX_ZP, 2, 3, "STX", AddressingMode::AddressingMode::Zeropage, Write, STX}},
    {INS_STX_ABS, {INS_STX_ABS, 3, 4, "STX", AddressingMode::AddressingMode::Absolute, Write, STX}},

    // Stack
    {INS_PHP_IMP, {INS_PHP_IMP, 1, 3, "PHP", AddressingMode::AddressingMode::Implicit, Write, PHP}},
    {INS_PLP_IMP, {INS_PLP_IMP, 1, 4, "PLP", AddressingMode::AddressingMode::Implicit, Read, PLP}},
    {INS_PHA_IMP, {INS_PHA_IMP, 1, 3, "PHA", AddressingMode::AddressingMode::Implicit, Write, PHA}},
    {INS_PLA_IMP, {INS_PLA_IMP, 1, 4, "PLA", AddressingMode::AddressingMode::Implicit, Read, PLA}},

    // Transfer
    {INS_TXA_IMP, {INS_TXA_IMP, 1, 2, "TXA", AddressingMode::AddressingMode::Implicit, Read, TXA}},
    {INS_TYA_IMP, {INS_TYA_IMP, 1, 2, "TYA", AddressingMode::AddressingMode::Implicit, Read, TYA}},
    {INS_TXS_IMP, {INS_TXS_IMP, 1, 2, "TXS", AddressingMode::AddressingMode::Implicit, Read, TXS}},
    {INS_TAY_IMP, {INS_TAY_IMP, 1, 2, "TAY", AddressingMode::AddressingMode::Implicit, Read, TAY}},
    {INS_TAX_IMP, {INS_TAX_IMP, 1, 2, "TAX", AddressingMode::AddressingMode::Implicit, Read, TAX}},
    {INS_TSX_IMP, {INS_TSX_IMP, 1, 2, "TSX", AddressingMode::AddressingMode::Implicit, Read, TSX}},

    // Compare
    {INS_CPY_IMM, {INS_CPY_IMM, 2, 2, "CPY", AddressingMode::AddressingMode::Immediate, Read, CPY}},
    {INS_CPY_ZP, {INS_CPY_ZP, 2, 3, "CPY", AddressingMode::AddressingMode::Zeropage, Read, CPY}},
    {INS_CPY_ABS, {INS_CPY_ABS, 3, 4, "CPY", AddressingMode::AddressingMode::Absolute, Read, CPY}},
    {INS_CMP_IMM, {INS_CMP_IMM, 2, 2, "CMP", AddressingMode::AddressingMode::Immediate, Read, CMP}},
    {INS_CMP_ZP, {INS_CMP_ZP, 2, 3, "CMP", AddressingMode::AddressingMode::Zeropage, Read, CMP}},
    {INS_CMP_ABS, {INS_CMP_ABS, 3, 4, "CMP", AddressingMode::AddressingMode::Absolute, Read, CMP}},
    {INS_CPX_IMM, {INS_CPX_IMM, 2, 2, "CPX", AddressingMode::AddressingMode::Immediate, Read, CPX}},
    {INS_CPX_ZP, {INS_CPX_ZP, 2, 3, "CPX", AddressingMode::AddressingMode::Zeropage, Read, CPX}},
    {INS_CPX_ABS, {INS_CPX_ABS, 3, 4, "CPX", AddressingMode::AddressingMode::Absolute, Read, CPX}},

    // Decrement
    {INS_DEY_IMP, {INS_DEY_IMP, 1, 2, "DEY", AddressingMode::AddressingMode::Implicit, Read, DEY}},
    {INS_DEX_IMP, {INS_DEX_IMP, 1, 2, "DEX", AddressingMode::AddressingMode::Implicit, Read, DEX}},
    {INS_DEC_ZP, {INS_DEC_ZP, 2, 5, "DEC", AddressingMode::AddressingMode::Zeropage, Read, DEC}},
    {INS_DEC_ABS, {INS_DEC_ABS, 3, 6, "DEC", AddressingMode::AddressingMode::Absolute, Read, DEC}},

    // Increment
    {INS_INY_IMP, {INS_INY_IMP, 1, 2, "INY", AddressingMode::AddressingMode::Implicit, Read, INY}},
    {INS_INX_IMP, {INS_INX_IMP, 1, 2, "INX", AddressingMode::AddressingMode::Implicit, Read, INX}},
    {INS_INC_ZP, {INS_INC_ZP, 2, 5, "INC", AddressingMode::AddressingMode::Zeropage, Read, INC}},
    {INS_INC_ABS, {INS_INC_ABS, 3, 6, "INC", AddressingMode::AddressingMode::Absolute, Read, INC}},

    // Branching
    {INS_BPL_REL, {INS_BPL_REL, 2, 2, "BPL", AddressingMode::AddressingMode::Relative, Read, BPL}},
    {INS_BMI_REL, {INS_BMI_REL, 2, 2, "BMI", AddressingMode::AddressingMode::Relative, Read, BMI}},
    {INS_BVC_REL, {INS_BVC_REL, 2, 2, "BVC", AddressingMode::AddressingMode::Relative, Read, BVC}},
    {INS_BVS_REL, {INS_BVS_REL, 2, 2, "BVS", AddressingMode::AddressingMode::Relative, Read, BVS}},
    {INS_BCC_REL, {INS_BCC_REL, 2, 2, "BCC", AddressingMode::AddressingMode::Relative, Read, BCC}},
    {INS_BCS_REL, {INS_BCS_REL, 2, 2, "BCS", AddressingMode::AddressingMode::Relative, Read, BCS}},
    {INS_BNE_REL, {INS_BNE_REL, 2, 2, "BNE", AddressingMode::AddressingMode::Relative, Read, BNE}},
    {INS_BEQ_REL, {INS_BEQ_REL, 2, 2, "BEQ", AddressingMode::AddressingMode::Relative, Read, BEQ}},

    {INS_NOP_IMP, {INS_NOP_IMP, 1, 2, "NOP", AddressingMode::AddressingMode::Implicit, Read, NOP}},
};

}  // namespace RT6502::InstructionSet