#include "6502/decode.h"

rt6502::decode::operation rt6502::decode::decode(Word pc, const Memory& memory) {
    const Byte opcode = fetch_byte(pc, memory);

    const auto& instr = instruction_set::opcode_list.at(opcode);

    Word param = 0;
    if (instr.bytes == 3)
        param = fetch_word(pc, memory);
    else if (instr.bytes == 2)
        param = fetch_byte(pc, memory);

    operation op = {
        instr,
        param
    };

    return op;
}

rt6502::instruction_set::instruction rt6502::decode::fetch_instruction(Word& pc, const Memory& memory) {
    const Byte opcode = fetch_byte(pc, memory);

    return instruction_set::opcode_list.at(opcode);
}

rt6502::Byte rt6502::decode::fetch_byte(Word& pc, const Memory& memory) noexcept {
    return memory[pc++];
}

rt6502::Word rt6502::decode::fetch_word(Word& pc, const Memory& memory) noexcept {
    const auto low_byte = fetch_byte(pc, memory);
    const auto high_byte = fetch_byte(pc, memory);
    Word result = high_byte;
    result <<= 8;
    result |= low_byte;
    return result;
}