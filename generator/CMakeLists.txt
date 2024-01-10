add_executable(generator generate.cpp)
target_link_libraries(generator PRIVATE ctre::ctre tl::expected)
target_include_directories(generator PRIVATE ../lib)