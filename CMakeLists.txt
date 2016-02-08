cmake_minimum_required(VERSION 3.3)
project(VM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp VirtualMachine.hpp Value.hpp Type.hpp OpCode.hpp Value.cpp Operand.hpp Lexer.hpp Lexer.cpp Operand.cpp VirtualMachine.cpp Command.hpp Command.cpp types.hpp Compare.hpp Equal.hpp)
add_executable(VM ${SOURCE_FILES})