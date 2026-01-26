#pragma once

#include "types.h"

namespace rt6502 {

class Memory {
   public:
    static constexpr uint32_t MAX_MEMORY = 1024 * 64;  // 64 Kb
    Byte data[MAX_MEMORY];

    Memory();

    void init() noexcept;

    Byte operator[](Word) const;
    Byte& operator[](Word);
};

}  // namespace rt6502