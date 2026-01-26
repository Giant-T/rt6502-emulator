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

struct metadata {
    Byte opcode;
    Byte bytes;
    std::string name;
    std::string format;
    void (*func)(Byte, CPU&);
};

inline const std::map<Byte, metadata> opcode_list = {
    {0xA9, {0xA9, 2, "LDA", " #{}", instruction_set::A9_LDA_IM}}
};

struct instruction {
    metadata info;
    Byte param;

    [[nodiscard]] std::string display() const {
        return std::vformat(info.name + info.format, std::make_format_args(param));
    }
};

instruction decode(Word&, const Memory&);

Byte fetch_byte(Word& pc, const Memory& memory) noexcept;

}  // namespace rt6502::decode