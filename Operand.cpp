#include "Operand.hpp"
#include "Lexer.hpp"

Operand::Operand(OpCode op, const Value& val) : _code(op), _value(val) { }

Operand Operand::Make(const std::string& code) {
#if DEBUG > 1
    std::cout << "Make: " << code << std::endl;
#endif
    Lexer lex(code);

    const OpCode op = lex.determine();
    const Value val = lex.parse();

    return Operand(op, val);
}

std::ostream& operator <<(std::ostream& out, const Operand& op) {
    switch (op.getCode()) {
        case OpCode::Variable:
            out << "Variable";
            break;
        case OpCode::Offset:
            out << "Offset";
            break;
        case OpCode::Value:
            out << "Value";
            break;
        default:
            out << "Unknown";
            break;
    }

    out << " => " << op.getValue();

    return out;
}