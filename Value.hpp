#ifndef VM_VALUE_HPP
#define VM_VALUE_HPP

#include <string>
#include <sstream>
#include "Type.hpp"
#include "types.hpp"

class Value {
private:
    union {
        i32_t _ival;
        f64_t _dval;
        bool  _bval;
        char  _cval;
    };

    std::string _str;

    Type _type;

public:
    Value() : _type(Type::Unknown) { }

    Value(i32_t val) : _ival(val), _type(Type::Integer) { }

    Value(f64_t val) : _dval(val), _type(Type::Decimal) { }

    Value(bool val) : _bval(val), _type(Type::Boolean) { }

    Value(char val) : _cval(val), _type(Type::Character) { }

    Value(const std::string& val) : _str(val), _type(Type::String) { }

    template<typename T>
    T getAs() const;

    i32_t getInteger() const {
        return _ival;
    }

    f64_t getDecimal() const {
        return _dval;
    }

    bool getBoolean() const {
        return _bval;
    }

    char getCharacter() const {
        return _cval;
    }

    const std::string& getString() const {
        return _str;
    }

    const Type getType() const {
        return _type;
    }
};

template<typename T>
T Value::getAs() const {
    switch (_type) {
        case Type::Integer:
            return static_cast<T>(_ival);
        case Type::Decimal:
            return static_cast<T>(_dval);
        case Type::Boolean:
            return static_cast<T>(_bval);
        case Type::Character:
            return static_cast<T>(_cval);
        case Type::String: {
            std::stringstream ss;
            ss << _str;

            int num;
            ss >> num;

            return static_cast<T>(num);
        }
    }

    std::stringstream ss;
    ss << "Type is: " << static_cast<int>(_type);

    throw ss.str();
}

std::ostream& operator <<(std::ostream&, const Value&);

#endif //VM_VALUE_HPP
