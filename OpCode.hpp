#ifndef VM_OPCODE_HPP
#define VM_OPCODE_HPP

#include "types.hpp"

enum class OpCode : u16_t {
    None,
    Value,
    Variable,
    Offset,
    Skip,
};

#endif //VM_OPCODE_HPP
