#pragma once

#include "types.h"

namespace RT6502 {

class Memory {
   public:
    static constexpr uint32_t MAX_MEMORY = 1024 * 64;  // 64 Kb
    Byte Data[MAX_MEMORY];

    Memory();

    void Init() noexcept;

    Byte operator[](Word) const;
    Byte& operator[](Word);
};

}  // namespace RT6502