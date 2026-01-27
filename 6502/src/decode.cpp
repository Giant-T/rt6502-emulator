#include "6502/decode.h"

rt6502::decode::operation rt6502::decode::decode(Word& pc, const Memory& memory) {
    const Byte opcode = fetch_byte(pc, memory);

    const auto& instr = opcode_list.at(opcode);

    Byte param = 0;
    if (instr.bytes > 1)
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