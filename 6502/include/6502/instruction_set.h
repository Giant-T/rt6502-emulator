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
    void (*func)(Byte, CPU&);

    std::string format() const noexcept {
        return addressing_mode::format(addr_mode);
    }
};

void LDA(Byte, CPU&);

inline const std::map<Byte, instruction> opcode_list = {
    {0xA9, {0xA9, 2, "LDA", addressing_mode::addressing_mode::immediate, LDA}},
    {0xA5, {0xA5, 2, "LDA", addressing_mode::addressing_mode::zeropage, LDA}},
    {0xAD, {0xAD, 3, "LDA", addressing_mode::addressing_mode::absolute, LDA}},
};

}  // namespace rt6502::instruction_set