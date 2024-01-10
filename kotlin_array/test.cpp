#include <iostream>
#include <ostream>

#include <pfw/AST.hpp>
#include <pfw/util.hpp>
#include "AST.hpp"
#include "parser.hpp"
#include "token.hpp"

#include <gtest/gtest.h>

using namespace kotlin_array;

void ToString(std::ostream& os, Node const& root, int indent = 0) {
    root.Visit(
        [&](NtNode const& n) {
            for (int i = 0; i < indent; ++i) {
                os << " ";
            }
            os << n.Label() << "\n";
            for (auto& c : n.Children()) {
                ToString(os, c, indent + 2);
            }
        },
        [&](TNode const& n) {
            for (int i = 0; i < indent; ++i) {
                os << " ";
            }
            os << n.Label() << "\n";
        });
}

TEST(KotlinArrayTest, TestAST) {
    std::string test = "var _Xa1 : Array<Int>, t : Array<X> ;";

    // Node expected =
    // NtNode("Program", {
    //     NtNode("Declaration", {
    //         TNode(VAR("var")),
    //         TNode(ID("_Xa1")),
    //         TNode(COLON(":")),
    //         TNode(ID("Array")),
    //         TNode(LANGLE("<")),
    //         NtNode("Type", {
    //             TNode(ID("Int"))
    //         }),
    //         TNode(RANGLE(">")),
    //         TNode(SEMICOLON(";"))
    //     })
    // });

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_TRUE(res.has_value());
    auto ast = res.value();

    // EXPECT_TRUE(expected == ast);

    std::cout << "AST: \n";
    ToString(std::cout, ast);
    std::cout << "\n";

    // std::cout << "Expected: \n";
    // ToString(std::cout, expected);
    // std::cout << "\n";
}

TEST(KotlinArrayTest, TestNotArray) {
    std::string test = "var x : Type<Int>;";

    Parser parser(test.begin(), test.end());
    auto res = parser.Parse();

    EXPECT_FALSE(res.has_value());

    std::cout << res.error() << "\n";
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