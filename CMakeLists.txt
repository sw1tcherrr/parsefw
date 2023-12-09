cmake_minimum_required(VERSION 3.25)
project(parsefw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ctre CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)

add_executable(playground main.cpp)
add_executable(t kotlin_func/test.cpp)

target_link_libraries(playground PRIVATE ctre::ctre tl::expected)
target_link_libraries(t PRIVATE ctre::ctre tl::expected)