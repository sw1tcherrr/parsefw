add_executable(testKotlinArray test.cpp)
target_link_libraries(testKotlinArray PRIVATE ctre::ctre tl::expected GTest::gtest GTest::gtest_main)

enable_testing()
add_test(KotlinArrayTest t)