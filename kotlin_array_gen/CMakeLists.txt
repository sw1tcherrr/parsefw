add_executable(testKotlinArrayGen test.cpp)
target_link_libraries(testKotlinArrayGen PRIVATE ctre::ctre tl::expected GTest::gtest GTest::gtest_main)
target_include_directories(testKotlinArrayGen PRIVATE ../lib)

enable_testing()
add_test(KotlinArrayTest t)