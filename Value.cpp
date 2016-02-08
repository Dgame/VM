#include "Value.hpp"

std::ostream& operator <<(std::ostream& out, const Value& val) {
    switch (val.getType()) {
        case Type::Integer:
            out << val.getInteger();
            break;
        case Type::Decimal:
            out << val.getDecimal();
            break;
        case Type::Boolean:
            out << val.getBoolean();
            break;
        case Type::Character:
            out << val.getCharacter();
            break;
        case Type::String:
            out << val.getString();
            break;
    }

    return out;
}