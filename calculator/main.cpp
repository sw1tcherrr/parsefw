#include <iostream>
#include <stdexcept>

#include "generated/AST.hpp"
#include "generated/parser.hpp"

int main() {
    std::string expr;
    std::cout << "> ";
    while (std::getline(std::cin, expr)) {
        calc::Parser p(expr.begin(), expr.end());
        auto ast_res = p.Parse();
        if (!ast_res) {
            std::cout << ast_res.error() << "\n";
            std::cout << "> ";
            continue;
        }
        auto ast = std::move(ast_res.value());

        auto* e = std::get_if<calc::exprNode>(&ast.Value());
        if (!e) {
            std::cout << "Unexpected AST root\n";
            return -1;
        }
        std::cout << e->val << "\n";
        std::cout << "> ";
    }
}