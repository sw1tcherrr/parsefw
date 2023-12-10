#include <iostream>
#include <ostream>

#include <AST.hpp>
#include <util.hpp>
#include "parser.hpp"

#include <gtest/gtest.h>

using namespace language::kotlin_func;
using namespace language::kotlin_func::ast;

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

TEST(Test, Test) {
    Node expected =
    NtNode("Declaration", {
        TNode(FUN("fun")),
        TNode(ID("f")),
        TNode(LPAREN("(")),
        NtNode("Args", {
            NtNode("Arg", {
                TNode(ID("param")),
                TNode(COLON(":")),
                NtNode("Type", {
                    TNode(ID("Int")),
                    NtNode("MaybeGeneric", {})
                })
            }),
            NtNode("MaybeArgs", {})
        }),
        TNode(RPAREN(")")),
        NtNode("MaybeReturnType", {})
    });

    std::string test = "fun f(param: Int)";
    Parser parser(test.begin(), test.end());

    auto ast = parser.Parse().value();

    ToString(std::cout, ast);
    std::cout << "\n";
    ToString(std::cout, expected);
    std::cout << "\n";

    bool res = (expected == ast);

    EXPECT_TRUE(res);
}