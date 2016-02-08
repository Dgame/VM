#ifndef VM_TYPE_HPP
#define VM_TYPE_HPP

#include "types.hpp"

enum class Type : u16_t {
    Unknown,
    Integer,
    Decimal,
    Character,
    Boolean,
    String,
};

#endif //VM_TYPE_HPP
