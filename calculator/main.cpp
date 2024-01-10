#include <iostream>
#include <stdexcept>

#include "generated/AST.hpp"
#include "generated/parser.hpp"

int main() {
    std::string expr;
    while (std::getline(std::cin, expr)) {
        calc::Parser p(expr.begin(), expr.end());
        auto ast_res = p.Parse();
        if (!ast_res) {
            std::cout << ast_res.error();
            continue;
        }
        auto ast = std::move(ast_res.value());

        std::cout << ast.Visit(
            [](calc::ENode const& e) { return e.val; },
            [](calc::TNode const& t) -> int { throw std::runtime_error("Unexpected AST root TNode"); },
            [](calc::EpNode const& ep) -> int { throw std::runtime_error("Unexpected AST root EpNode"); },
            [](calc::_TokenNode const& tn) -> int { throw std::runtime_error("Unexpected AST root _TokenNode"); }
        ) << "\n";
    }
}