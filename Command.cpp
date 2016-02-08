#include "Command.hpp"

const std::map<std::string, u16_t> Command::Commands = {
        {"assign",            Command::Assign},
        {"add",               Command::Add},
        {"sub",               Command::Sub},
        {"mul",               Command::Mul},
        {"div",               Command::Div},
        {"print",             Command::Print},
        {"skip",              Command::Skip},
        {"skip_if",           Command::SkipIf},
        {"skip_if_not",       Command::SkipIfNot},
        {"is_equal",          Command::IsEqual},
        {"is_not_equal",      Command::IsNotEqual},
        {"is_lower",          Command::IsLower},
        {"is_lower_or_equal", Command::IsLowerOrEqual}
};

Command::Command(const std::string& code) {
    auto space_pos = code.find(' ');

    auto cmd = code.substr(0, space_pos);
    auto it  = Commands.find(cmd);
    if (it != Commands.end()) {
        this->command = it->second;
    } else {
        throw "Unknown command";
    }

    auto comma_pos = code.find(',', space_pos);
    if (comma_pos != std::string::npos) {
        this->operands.first  = Operand::Make(code.substr(space_pos + 1, comma_pos));
        this->operands.second = Operand::Make(code.substr(comma_pos + 1));
    } else {
        this->operands.first = Operand::Make(code.substr(space_pos + 1));
    }
}
