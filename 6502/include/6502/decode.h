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

#include "instruction_set.h"
#include "memory.h"
#include "types.h"

namespace rt6502::decode {

struct operation {
    instruction_set::instruction info;
    Word param;

    [[nodiscard]] std::string display() const {
        return std::vformat(info.name + " " + info.format(), std::make_format_args(param));
    }
};

operation decode(Word&, const Memory&);

instruction_set::instruction fetch_instruction(Word& pc, const Memory& memory);

Byte fetch_byte(Word& pc, const Memory& memory) noexcept;

}  // namespace rt6502::decode