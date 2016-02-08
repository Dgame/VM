#include "VirtualMachine.hpp"
#include "Operand.hpp"

#include <string.h>
#include <iostream>
#include <cmath>
#include <limits>

void VirtualMachine::assign(const std::pair<Operand, Operand>& ops) {
#if DEBUG
    std::cout << "ASSIGN" << std::endl;
#endif
    // TODO: assert(lhs.code == OpCode::Variable);
    const i16_t vi = ops.first.getValue().getAs<i16_t>();
    const Value& val = this->unpack(ops.second);

    if (_variables.size() <= vi) {
        _variables.push_back(val);
    } else {
        _variables[vi] = val;
    }
}

const Value& VirtualMachine::unpack(const Operand& op) {
#if DEBUG
    std::cout << "EXTRACT" << std::endl;
#endif
    switch (op.getCode()) {
        case OpCode::Variable:
#if DEBUG
            std::cout << "\tVARIABLE " << op.getValue() << '(' << _variables.at(op.getValue().getAs<u16_t>()) << ')' <<
            std::endl;
#endif
            return _variables.at(op.getValue().getAs<u16_t>());
        case OpCode::Offset: {
            const u16_t offset = op.getValue().getAs<u16_t>();
#if DEBUG
            std::cout << "\tOFFSET " << op.getValue() << '(' << _stack.at(offset) << ')' <<
            std::endl;
#endif
            _stack_offset -= offset + 1;

            return _stack.at(offset);
        }
        case OpCode::Value:
#if DEBUG
            std::cout << "\tVALUE " << op.getValue() << std::endl;
#endif
            return op.getValue();
        case OpCode::Skip:
#if DEBUG
            std::cout << "\tSKIP " << op.getValue() << std::endl;
#endif
            return op.getValue();
    }

    throw "Could not unpack";
}

void VirtualMachine::add(const std::pair<Operand, Operand>& ops) {
#if DEBUG
    std::cout << "ADD" << std::endl;
#endif
    const f64_t result = this->unpack(ops.first).getAs<f64_t>() + this->unpack(ops.second).getAs<f64_t>();
#if DEBUG
    std::cout << "\t = " << result << std::endl;
#endif
    this->push(result);
}

void VirtualMachine::sub(const std::pair<Operand, Operand>& ops) {
#if DEBUG
    std::cout << "SUB" << std::endl;
#endif
    const f64_t result = this->unpack(ops.first).getAs<f64_t>() - this->unpack(ops.second).getAs<f64_t>();
#if DEBUG
    std::cout << "\t = " << result << std::endl;
#endif
    this->push(result);
}

void VirtualMachine::mul(const std::pair<Operand, Operand>& ops) {
#if DEBUG
    std::cout << "MUL" << std::endl;
#endif
    const f64_t result = this->unpack(ops.first).getAs<f64_t>() * this->unpack(ops.second).getAs<f64_t>();
#if DEBUG
    std::cout << "\t = " << result << std::endl;
#endif
    this->push(result);
}

void VirtualMachine::div(const std::pair<Operand, Operand>& ops) {
#if DEBUG
    std::cout << "DIV" << std::endl;
#endif
    const f64_t result = this->unpack(ops.first).getAs<f64_t>() / this->unpack(ops.second).getAs<f64_t>();
#if DEBUG
    std::cout << "\t = " << result << std::endl;
#endif
    this->push(result);
}

void VirtualMachine::print(const Operand& op) {
#if DEBUG
    std::cout << "PRINT" << std::endl;
#endif
    std::cout << this->unpack(op) << std::endl;
}

void VirtualMachine::push(const Value& val) {
#if DEBUG
    std::cout << "PUSH (" << val << ')' << std::endl;
#endif
    _stack_offset++;
    _stack[_stack_offset - 1] = val;
}

VirtualMachine* VirtualMachine::equal(const std::pair<Operand, Operand>& ops) {
    const Value& v1 = this->unpack(ops.first);
    const Value& v2 = this->unpack(ops.second);

    if (v1.getType() == Type::String && v2.getType() == Type::String) {
        _compare = v1.getString() == v2.getString();
    } else if (v1.getType() == v2.getType() &&
               (v1.getType() == Type::Integer ||
                v1.getType() == Type::Boolean ||
                v1.getType() == Type::Character)) {
        _compare = v1.getAs<i32_t>() == v2.getAs<i32_t>();
    } else {
        _compare = std::fabs(v1.getAs<f32_t>() - v2.getAs<f32_t>()) < std::numeric_limits<f32_t>::epsilon();
    }

    return this;
}

VirtualMachine* VirtualMachine::lower(const std::pair<Operand, Operand>& ops) {
    const Value& v1 = this->unpack(ops.first);
    const Value& v2 = this->unpack(ops.second);

    if (v1.getType() == Type::String && v2.getType() == Type::String) {
        _compare = strcmp(v1.getString().c_str(), v2.getString().c_str()) == -1;
    } else if (v1.getType() == v2.getType() &&
               (v1.getType() == Type::Integer ||
                v1.getType() == Type::Boolean ||
                v1.getType() == Type::Character)) {
//        std::cout << "Lower " << v1.getAs<i32_t>() << "::" <<  v2.getAs<i32_t>() << std::endl;
        _compare = v1.getAs<i32_t>() < v2.getAs<i32_t>();
    } else {
        _compare = v1.getAs<f32_t>() < v2.getAs<f32_t>();
    }

    return this;
}