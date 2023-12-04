#include <fstream>
#include <iostream>

#include "kotlin_func/lexer.hpp"
#include "kotlin_func/parser.hpp"
#include "kotlin_func/token.hpp"
#include "lib/graphviz.hpp"
#include "lib/mmap_buffer.hpp"

int main() {
    using namespace language::kotlin_func;
    using namespace pfw;

    auto test = MakeMmap("test.txt").value();

    Lexer lex(test.begin(), test.begin());
    while (true) {
        Token tok = lex.NextToken();
        std::cout << tok;
        if (tok.index() == 0) {
            break;
        }
    }

    Parser p(test.begin(), test.end());
    auto ast = p.Parse().value();
    auto out = std::ofstream("ast.dot");
    pfw::graphviz::AstToDot(out, ast);
}