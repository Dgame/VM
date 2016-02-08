#ifndef VM_OPERAND_HPP
#define VM_OPERAND_HPP

#include "OpCode.hpp"
#include "Value.hpp"

class Operand {
private:
    OpCode _code;
    Value _value;

public:
    Operand() = default;
    explicit Operand(OpCode, const Value&);

    static Operand Make(const std::string&);

    OpCode getCode() const {
        return _code;
    }

    const Value& getValue() const {
        return _value;
    }
};

std::ostream& operator <<(std::ostream&, const Operand&);

#endif //VM_OPERAND_HPP
