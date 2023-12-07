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

    auto buf_res = MakeMmap("test.txt");
    if (!buf_res) { 
        std::cerr << buf_res.error();
        return -1;
    }
    auto buf = std::move(buf_res.value());

    Lexer lex(buf.begin(), buf.end());
    while (true) {
        Token tok = lex.NextToken();
        std::cout << tok << "\n";
        if (tok.index() == 0) {
            break;
        }
    }

    Parser p(buf.begin(), buf.end());
    auto ast_res = p.Parse();
    if (!ast_res) {
        std::cerr << ast_res.error();
        return -1;
    }
    auto ast = std::move(ast_res.value());

    auto out = std::ofstream("ast.dot");
    pfw::graphviz::AstToDot(out, ast);
}