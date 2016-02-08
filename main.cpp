#include <string>
#include <iostream>
#include "VirtualMachine.hpp"
#include "Command.hpp"

int main() {
    const std::vector<std::string> Code = {
            "assign &0, 42",
            "print &0",
            "assign &1, 23",
            "print &1",
            "add &0, &1",
            "assign &2, ~0",
            "print &2",
            "print 'Hallo Welt'",
            "print 42",
            "print 3.14",
            "is_lower &0, &1",
            "skip_if_not #2",
            "print 'a is lower than b'",
            "skip #1",
            "print 'b is lower than a'",
            "assign &3, 0",
            "is_lower &3, 5",
            "skip_if_not #4",
            "print &3",
            "add &3, 1",
            "assign &3, ~0",
            "skip #-5"
    };

    VirtualMachine vm;

    for (u32_t i = 0; i < Code.size(); i++) {
        try {
            const Command cmd(Code[i]);
            switch (cmd.command) {
                case Command::Assign:
                    vm.assign(cmd.operands);
                    break;
                case Command::Add:
                    vm.add(cmd.operands);
                    break;
                case Command::Sub:
                    vm.sub(cmd.operands);
                    break;
                case Command::Mul:
                    vm.mul(cmd.operands);
                    break;
                case Command::Div:
                    vm.div(cmd.operands);
                    break;
                case Command::Print:
                    vm.print(cmd.operands.first);
                    break;
                case Command::IsEqual:
                    vm.equal(cmd.operands);
                    break;
                case Command::IsNotEqual:
                    vm.equal(cmd.operands)->falsify();
                    break;
                case Command::IsLower:
                    vm.lower(cmd.operands);
//                    std::cout << "is Lower " << (vm.getCompare() ? 1 : 0) << std::endl;
                    break;
                case Command::IsLowerOrEqual:
                    vm.lower(cmd.operands);
                    if (!vm.getCompare())
                        vm.equal(cmd.operands);
                    break;
                case Command::SkipIf:
                    if (vm.getCompare()) {
//                        std::cout << "SKIP IF" << std::endl;
                        i += cmd.operands.first.getValue().getInteger();
//                        std::cout << Code[i] << std::endl;
                    }
                    break;
                case Command::SkipIfNot:
                    if (!vm.getCompare()) {
//                        std::cout << "SKIP IF NOT" << std::endl;
                        i += cmd.operands.first.getValue().getInteger();
//                        std::cout << Code[i] << std::endl;
                    }
                    break;
                case Command::Skip: {
                    const i32_t offset = cmd.operands.first.getValue().getInteger();
                    i += offset;
                    if (offset < 0) {
                        i--;
                    }
                }
                    break;
            }
        } catch (const char* err) {
            std::cerr << err << std::endl;
        }
    }
}
