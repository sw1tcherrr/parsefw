cmake_minimum_required(VERSION 3.25)
project(parser_framework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(playground main.cpp lib/AST.hpp lib/graphviz.hpp)
