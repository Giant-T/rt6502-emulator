#include "6502/decode.h"

RT6502::Decode::Operation RT6502::Decode::Decode(Word pc, const Memory& memory) {
    const Byte opcode = FetchByte(pc, memory);

    const auto& instr = InstructionSet::OPCODE_LIST.at(opcode);

    Word param = 0;
    if (instr.Bytes == 3)
        param = FetchWord(pc, memory);
    else if (instr.Bytes == 2)
        param = FetchByte(pc, memory);

    return {
        .Info = instr,
        .Param = param
    };
}

const RT6502::InstructionSet::Instruction& RT6502::Decode::FetchInstruction(Word& pc, const Memory& memory) {
    const Byte opcode = FetchByte(pc, memory);

    return InstructionSet::OPCODE_LIST.at(opcode);
}

RT6502::Byte RT6502::Decode::FetchByte(Word& pc, const Memory& memory) noexcept {
    return memory[pc++];
}

RT6502::Word RT6502::Decode::FetchWord(Word& pc, const Memory& memory) noexcept {
    const auto lowByte = FetchByte(pc, memory);
    const auto highByte = FetchByte(pc, memory);
    Word result = 0;
    result.Low = lowByte;
    result.High = highByte;
    return result;
}