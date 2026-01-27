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

namespace rt6502::instruction_set {

struct instruction {
    Byte opcode;
    Byte bytes;
    std::string name;
    const addressing_mode::addressing_mode addr_mode;
    void (*func)(Byte, CPU&, Memory&);

    std::string format() const noexcept {
        return addressing_mode::format(addr_mode);
    }
};

void LDA(Byte, CPU&, Memory&);
void TSX(Byte, CPU&, Memory&);
void PHA(Byte, CPU&, Memory&);

inline const std::map<Byte, instruction> opcode_list = {
    {0xA9, {0xA9, 2, "LDA", addressing_mode::addressing_mode::immediate, LDA}},
    {0xA5, {0xA5, 2, "LDA", addressing_mode::addressing_mode::zeropage, LDA}},
    {0xAD, {0xAD, 3, "LDA", addressing_mode::addressing_mode::absolute, LDA}},
    {0xBA, {0xBA, 1, "TSX", addressing_mode::addressing_mode::implicit, TSX}},
    {0x48, {0x48, 1, "PHA", addressing_mode::addressing_mode::implicit, PHA}},
};

}  // namespace rt6502::instruction_set