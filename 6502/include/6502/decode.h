/**
 * Fonctions de décodage des instructions 6502.
 *
 * @file decode.h
 * @authors Nicolas Béland
 * @date 2026-01-23
 */

#pragma once

#include <format>
#include <map>
#include <string>

#include "addressing_mode.h"
#include "instruction_set.h"
#include "memory.h"
#include "types.h"

namespace rt6502::decode {

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

inline const std::map<Byte, instruction> opcode_list = {
    {0xA9, {0xA9, 2, "LDA", addressing_mode::addressing_mode::immediate, instruction_set::LDA}},
    {0xA5, {0xA5, 2, "LDA", addressing_mode::addressing_mode::zeropage, instruction_set::LDA}},
    {0xAD, {0xAD, 3, "LDA", addressing_mode::addressing_mode::absolute, instruction_set::LDA}},
};

struct operation {
    instruction info;
    Word param;

    [[nodiscard]] std::string display() const {
        return std::vformat(info.name + " " + info.format(), std::make_format_args(param));
    }
};

operation decode(Word&, const Memory&);

instruction fetch_instruction(Word& pc, const Memory& memory);

Byte fetch_byte(Word& pc, const Memory& memory) noexcept;

}  // namespace rt6502::decode