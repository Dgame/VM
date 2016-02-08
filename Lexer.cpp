#include "Lexer.hpp"
#include "types.hpp"
#include <iostream>

Lexer::Lexer(const std::string& str) : _p(&str[0]) { }

void Lexer::skipSpace() {
    while (isspace(*_p)) {
        _p++;
    }
}

std::string Lexer::getString(char stop) {
    std::string str;
    str.reserve(32);

    _p++;
    while (*_p != stop) {
        str += *_p;
        _p++;
    }

    return str;
}

Value Lexer::parse() {
    this->skipSpace();

    bool neg = false;
    if (*_p == '-') {
        _p++;
        neg = true;
    }

    if (isdigit(*_p)) {
        i32_t ival = 0;
        while (isdigit(*_p)) {
            ival *= 10;
            ival += static_cast<int>(*_p - '0');

            _p++;
        }

        if (*_p == '.') {
            _p++;

            f32_t pot = 1;
            f32_t dec = 0;
            do {
                pot *= 10;
                dec *= 10;
                dec += *_p - '0';

                _p++;
            } while (isdigit(*_p));

            const f64_t dval = ival + (dec / pot);

            return neg ? (dval * -1) : dval;
        }

        return neg ? (ival * -1) : ival;
    }

    if (*_p == '"') {
        return this->getString('"');
    }

    if (*_p == '\'') {
        return this->getString('\'');
    }

    std::cerr << _p << std::endl;

    throw "No type!";
}

OpCode Lexer::determine() {
    this->skipSpace();
#if DEBUG > 1
    std::cout << " ~> (before) " << _p << std::endl;
#endif
    OpCode op;
    if (*_p == '&') {
        op = OpCode::Variable;
        _p++;
    } else if (*_p == '~') {
        op = OpCode::Offset;
        _p++;
    } else if (*_p == '#') {
        op = OpCode::Skip;
        _p++;
    } else {
        op = OpCode::Value;
    }
#if DEBUG > 1
    std::cout << " ~> (after) " << _p << std::endl;
#endif
    return op;
}
