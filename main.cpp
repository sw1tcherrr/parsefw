#include <iostream>
#include <fstream>

#include "kotlin_func/parser.hpp"
#include "lib/graphviz.hpp"

int main() {
    using namespace language::kotlin_func;
    using namespace parsefw;

    std::string test = "fun funCtion(a: Array<List<Int>>, b: Double)  : Set<Map<K>>";
    std::cout << test << "\n";

//    lexer lex(test.begin(), test.end());
//    while (true) {
//        auto tok = lex.next_token();
//        std::cout << tok;
//        if (is_eof(tok)) { break; }
//    }
//
//
//    std::ifstream f("../test.txt");
//    lexer lex2(std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>{});
//    while (true) {
//        auto tok = lex2.next_token();
//        std::cout << tok;
//        if (is_eof(tok)) { break; }
//    }

    parser p(test.begin(), test.end());
    auto ast = p.parse().value();
    auto out = std::ofstream("../ast.dot");
    parsefw::graphviz::AST_to_DOT(out, ast);

    std::cout << "\n";

    std::ifstream f("../test.txt");
    parser p2(std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>{});
    auto ast2 = p2.parse().value();
    auto out2 = std::ofstream("../ast2.dot");
    parsefw::graphviz::AST_to_DOT(out2, ast2);
}