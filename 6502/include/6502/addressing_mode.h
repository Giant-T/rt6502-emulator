#pragma once

#include <string>

#include "6502/memory.h"
#include "types.h"

namespace rt6502::addressing_mode {
enum class addressing_mode {
    implicit,
    accumulator,
    immediate,
    zeropage,
    zeropage_x,
    zeropage_y,
    relative,
    absolute,
    absolute_x,
    absolute_y,
    indirect,
    indexed_indirect,
    indirect_indexed
};

std::string format(addressing_mode);
Byte execute(addressing_mode, Word&, const Memory&);

Byte immediate(Word& pc, const Memory& memory);
Byte zeropage(Word& pc, const Memory& memory);
Byte absolute(Word& pc, const Memory& memory);

}  // namespace rt6502::addressing_mode