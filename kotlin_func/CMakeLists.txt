add_executable(testKotlinFunc test.cpp)
target_link_libraries(testKotlinFunc PRIVATE ctre::ctre tl::expected GTest::gtest GTest::gtest_main)
target_include_directories(testKotlinFunc PRIVATE ../lib)

enable_testing()
add_test(KotlinFuncTest t)