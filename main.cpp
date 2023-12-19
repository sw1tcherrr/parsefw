#include <fstream>
#include <iostream>

#include "kotlin_array/lexer.hpp"
#include "kotlin_array/parser.hpp"
#include "kotlin_array/token.hpp"
#include "lib/graphviz.hpp"
#include "lib/mmap_buffer.hpp"

int main() {
    using namespace kotlin_array;
    using namespace pfw;

    auto buf_res = MakeMmap("test.txt");
    if (!buf_res) { 
        std::cerr << buf_res.error();
        return -1;
    }
    auto buf = std::move(buf_res.value());

    Lexer lex(buf.begin(), buf.end());
    while (true) {
        auto t = lex.NextToken();
        if (!t) {
            std::cerr << t.error();
            break;
        }
        Token tok = t.value();
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