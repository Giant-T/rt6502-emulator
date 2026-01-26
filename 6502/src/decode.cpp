#include "6502/decode.h"

rt6502::decode::instruction rt6502::decode::decode(Word& pc, const Memory& memory) {
    const Byte ins = fetch_byte(pc, memory);

    const auto& meta = opcode_list.at(ins);

    Byte param = 0;
    if (meta.bytes > 1)
        param = fetch_byte(pc, memory);

    instruction inst = {
        meta,
        param
    };

    return inst;
}

rt6502::Byte rt6502::decode::fetch_byte(Word& pc, const Memory& memory) noexcept {
    return memory[pc++];
}