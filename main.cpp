#include <fstream>
#include <iostream>

#include "kotlin_func/lexer.hpp"
#include "kotlin_func/parser.hpp"
#include "kotlin_func/token.hpp"
#include "lib/graphviz.hpp"

int main() {
    using namespace language::kotlin_func;
    using namespace pfw;

    std::string test = "fun funCtion(a: Array<List<Int>>, b: Double)  : Set<Map<K>>";
    std::cout << test << "\n";

    Lexer lex(test.begin(), test.end());
    while (true) {
        Token tok = lex.NextToken();
        std::cout << tok;
        if (tok.index() == 0) {
            break;
        }
    }

    /*
        std::ifstream f("../test.txt");
        lexer lex2(std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>{});
        while (true) {
            auto tok = lex2.next_token();
            std::cout << tok;
            if (is_eof(tok)) { break; }
        }
    */

    Parser p(test.begin(), test.end());
    auto ast = p.Parse().value();
    auto out = std::ofstream("../ast.dot");
    pfw::graphviz::AstToDot(out, ast);

    // todo wrap input iterator of fstream to make bidirectional iterator
    /*
        std::cout << "\n";

        std::ifstream f("../test.txt");
        parser p2(std::istreambuf_iterator<char>{f}, std::istreambuf_iterator<char>{});
        auto ast2 = p2.parse().value();
        auto out2 = std::ofstream("../ast2.dot");
        parsefw::graphviz::AST_to_DOT(out2, ast2);
    */
}