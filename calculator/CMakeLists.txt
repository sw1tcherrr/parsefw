add_executable(calculator main.cpp)

target_link_libraries(calculator PRIVATE ctre::ctre tl::expected)
target_include_directories(calculator PRIVATE ../lib)
