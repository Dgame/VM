#ifndef VM_VM_HPP
#define VM_VM_HPP

#include <vector>
#include <array>
#include <utility>
#include "Value.hpp"

#define DEBUG 0

struct Operand;

class VirtualMachine {
private:
    std::vector<Value>   _variables;
    std::array<Value, 8> _stack;

    u16_t _stack_offset = 0;
    bool  _compare      = false;

public:
    bool getCompare() const {
        return _compare;
    }

    void assign(const std::pair<Operand, Operand>&);

    const Value& unpack(const Operand&);

    void add(const std::pair<Operand, Operand>&);

    void sub(const std::pair<Operand, Operand>&);

    void mul(const std::pair<Operand, Operand>&);

    void div(const std::pair<Operand, Operand>&);

    void print(const Operand&);

    void push(const Value&);

    VirtualMachine* equal(const std::pair<Operand, Operand>&);

    VirtualMachine* lower(const std::pair<Operand, Operand>&);

    VirtualMachine* falsify() {
        _compare = !_compare;

        return this;
    }
};

#endif //VM_VM_HPP
