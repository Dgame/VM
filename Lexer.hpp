#ifndef VM_LEXER_HPP
#define VM_LEXER_HPP

#include <string>
#include "Value.hpp"
#include "OpCode.hpp"

class Lexer {
private:
    const char* _p;

public:
    explicit Lexer(const std::string&);

    void skipSpace();

    std::string getString(char);

    Value parse();

    OpCode determine();
};

#endif //VM_LEXER_HPP
