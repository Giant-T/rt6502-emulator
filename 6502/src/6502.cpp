#include "6502/6502.h"

void rt6502::rt6502::reset() noexcept {
    cpu.reset(memory);
}
