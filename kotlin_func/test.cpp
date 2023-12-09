#include <iostream>
#include <ostream>

#include "AST.hpp"
#include "../lib/util.hpp"

using namespace language::kotlin_func;
using namespace language::kotlin_func::ast;

void ToString(std::ostream& os, Node const& root) {
    root.Visit(
        [&](NtNode const& n) {
            for (auto& c : n.Children()) {
                ToString(os, c);
            }
        },
        [&](TNode const& n) {
            os << n.Label() << " ";
        });
}

int main() {
    Node root =
    NtNode("Declaration", {
        TNode(FUN("fun")),
        TNode(ID("f")),
        TNode(LPAREN("(")),
        NtNode("Args", {
            NtNode("Arg", {
                TNode(ID("param")),
                TNode(COLON(":")),
                NtNode("Type", {
                    TNode(ID("Int"))
                })
            })
        }),
        TNode(RPAREN(")"))
    });

    ToString(std::cout, root);
    std::cout << "\n";

    Node root2 =
    NtNode("Declaration", {
        TNode(FUN("fun")),
        TNode(ID("F")),
        TNode(LPAREN("(")),
        NtNode("Args", {
            NtNode("Arg", {
                TNode(ID("a")),
                TNode(COLON(":")),
                NtNode("Type", {
                    TNode(ID("Int"))
                })
            })
        }),
        TNode(RPAREN(")"))
    });

    ToString(std::cout, root2);
    std::cout << "\n";

    std::cout << (root == root) << " " << (root == root2);
}