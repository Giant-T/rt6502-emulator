#include "6502/decode.h"

rt6502::decode::operation rt6502::decode::decode(Word& pc, const Memory& memory) {
    const Byte opcode = fetch_byte(pc, memory);

    const auto& instr = opcode_list.at(opcode);

    Word param = 0;
    if (instr.bytes == 3) {
        const Byte low = fetch_byte(pc, memory);
        const Byte high = fetch_byte(pc, memory);
        param = high;
        param <<= 8;
        param |= low;
    }
    if (instr.bytes == 2)
        param = fetch_byte(pc, memory);

    operation op = {
        instr,
        param
    };

    return op;
}

rt6502::decode::instruction rt6502::decode::fetch_instruction(Word& pc, const Memory& memory) {
    const Byte opcode = fetch_byte(pc, memory);

    return opcode_list.at(opcode);
}

rt6502::Byte rt6502::decode::fetch_byte(Word& pc, const Memory& memory) noexcept {
    return memory[pc++];
}