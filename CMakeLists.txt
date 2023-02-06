cmake_minimum_required(VERSION 3.25)
project(parser_framework)

set(CMAKE_CXX_STANDARD 20)

add_executable(playground main.cpp lib/AST.hpp lib/graphviz.hpp)
