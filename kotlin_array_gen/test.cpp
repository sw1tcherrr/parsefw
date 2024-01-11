#include <iostream>
#include <ostream>

#include <pfw/AST.hpp>
#include <pfw/util.hpp>
#include "generated/AST.hpp"
#include "generated/parser.hpp"
#include <pfw/graphviz.hpp>

#include <gtest/gtest.h>

using namespace kotlin_array;

TEST(KotlinArrayTest, TestAST) {
    std::string test = "var _Xa1 : Array<Int>, t : Array<X> ;";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_TRUE(res.has_value());
    auto ast = res.value();

    auto out = std::ofstream("ast.dot");
    pfw::graphviz::AstToDot(out, ast);
}


TEST(KotlinArrayTest, TestUnbalanced) {
    std::string test = "var x : Array < Int ;";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
}

TEST(KotlinArrayTest, TestNoSemicolon) {
    std::string test = "var x : Array<Int>";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
}

TEST(KotlinArrayTest, TestNoEof) {
    std::string test = "var x : Array<Int>; var y";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
}

TEST(KotlinArrayTest, TestUnexpectedSymbol) {
    std::string test = "var x : ! Array<Int>; var y";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
}

TEST(KotlinArrayTest, TestInvalidId) {
    std::string test = "var 1 : Array<Int>;";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
}