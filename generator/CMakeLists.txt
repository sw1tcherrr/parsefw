add_executable(generator generate.cpp)
target_link_libraries(generator PRIVATE ctre::ctre tl::expected)