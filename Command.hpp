#ifndef VM_COMMAND_HPP
#define VM_COMMAND_HPP

#include <utility>
#include <map>
#include "Operand.hpp"
#include "types.hpp"

struct Command {
    enum {
        Assign,
        Add,
        Sub,
        Mul,
        Div,
        Print,
        Skip,
        SkipIf,
        SkipIfNot,
        IsEqual,
        IsNotEqual,
        IsLower,
        IsLowerOrEqual
    };

    static const std::map<std::string, u16_t> Commands;

    int command;
    std::pair<Operand, Operand> operands;

    explicit Command(const std::string&);
};

#endif //VM_COMMAND_HPP
