/**
 * Fonctions de décodage des instructions 6502.
 *
 * @file decode.h
 * @authors Nicolas Béland
 * @date 2026-01-23
 */

#pragma once

#include <format>
#include <string>

#include "instruction_set.h"
#include "memory.h"
#include "types.h"

namespace RT6502::Decode {

struct Operation {
    InstructionSet::Instruction Info;
    Word Param;

    [[nodiscard]] std::string Display() const {
        return std::vformat(std::string(Info.Name) + " " + std::string(Info.Format()), std::make_format_args(Param));
    }
};

Operation Decode(Word, const Memory&);

const InstructionSet::Instruction& FetchInstruction(Word& pc, const Memory& memory);

Byte FetchByte(Word& pc, const Memory& memory) noexcept;
Word FetchWord(Word& pc, const Memory& memory) noexcept;

}  // namespace RT6502::Decode