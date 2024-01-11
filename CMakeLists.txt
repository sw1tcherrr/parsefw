cmake_minimum_required(VERSION 3.25)
project(parsefw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(ctre CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(playground main.cpp)

target_link_libraries(playground PRIVATE ctre::ctre tl::expected)
target_include_directories(playground PRIVATE lib)

add_subdirectory(kotlin_func)
add_subdirectory(kotlin_array)
add_subdirectory(generator)

add_subdirectory(calculator)
add_subdirectory(kotlin_array_gen)
