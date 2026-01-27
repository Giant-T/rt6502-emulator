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
    const AddressingMode::AddressingMode AddrMode;
    void (*Func)(Byte, CPU&, Memory&);

    std::string Format() const noexcept {
        return AddressingMode::Format(AddrMode);
    }
};

void LDA(Byte, CPU&, Memory&);
void TSX(Byte, CPU&, Memory&);
void PHA(Byte, CPU&, Memory&);

inline const std::map<Byte, Instruction> OPCODE_LIST = {
    {0xA9, {0xA9, 2, "LDA", AddressingMode::AddressingMode::Immediate, LDA}},
    {0xA5, {0xA5, 2, "LDA", AddressingMode::AddressingMode::Zeropage, LDA}},
    {0xAD, {0xAD, 3, "LDA", AddressingMode::AddressingMode::Absolute, LDA}},
    {0xBA, {0xBA, 1, "TSX", AddressingMode::AddressingMode::Implicit, TSX}},
    {0x48, {0x48, 1, "PHA", AddressingMode::AddressingMode::Implicit, PHA}},
};

}  // namespace RT6502::InstructionSet