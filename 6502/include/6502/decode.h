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

namespace RT6502::Decode {

struct Operation {
    InstructionSet::Instruction Info;
    Word Param;

    [[nodiscard]] std::string Display() const {
        return std::vformat(Info.Name + " " + Info.Format(), std::make_format_args(Param));
    }
};

Operation Decode(Word, const Memory&);

InstructionSet::Instruction FetchInstruction(Word& pc, const Memory& memory);

Byte FetchByte(Word& pc, const Memory& memory) noexcept;
Word FetchWord(Word& pc, const Memory& memory) noexcept;

}  // namespace RT6502::Decode