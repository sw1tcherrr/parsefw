add_executable(t test.cpp)
target_link_libraries(t PRIVATE ctre::ctre tl::expected GTest::gtest GTest::gtest_main)
target_include_directories(t PRIVATE ../lib)

enable_testing()
add_test(KotlinFuncTest t)