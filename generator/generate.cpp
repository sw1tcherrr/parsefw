#include <cctype>
#include <string>
#include <unordered_map>
#include <format>
#include <iostream>

#include <pfw/util.hpp>
#include "generator.hpp"
#include "rule.hpp"
#include "grammar.hpp"

#include <GrammarParser.h>
#include <GrammarLexer.h>
#include <TokensLexer.h>
#include <TokensParser.h>
#include <antlr4-runtime.h>

using namespace pfw::gen;

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Usage: generator <namespace> <grammar file> <token file> <output dir>\n";
    }

    std::string_view ns    = argv[1];
    std::string_view gfile = argv[2];
    std::string_view tfile = argv[3];
    std::string_view out   = argv[4];

    std::ifstream grammar_file(gfile.data());
    antlr4::ANTLRInputStream grammar_input(grammar_file);
    GrammarLexer grammar_lexer(&grammar_input);
    antlr4::CommonTokenStream grammar_token_stream(&grammar_lexer);
    GrammarParser grammar_parser(&grammar_token_stream);

    std::ifstream tokens_file(tfile.data());
    antlr4::ANTLRInputStream tokens_input(tokens_file);
    TokensLexer tokens_lexer(&tokens_input);
    antlr4::CommonTokenStream tokens_token_stream(&tokens_lexer);
    TokensParser tokens_parser(&tokens_token_stream);

    grammar_parser.grammar_();
    tokens_parser.grammar_();
    Grammar g(std::move(grammar_parser.rules), std::move(grammar_parser.start));

    std::cout << "FIRST\n";
    for (auto const& [k, v] : g.FIRST) {
        std::cout << k << " : ";
        for (auto const& t : v) {
            std::cout << t << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "\nFOLLOW\n";
    for (auto const& [k, v] : g.FOLLOW) {
        std::cout << k << " : ";
        for (auto const& t : v) {
            std::cout << t << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "\nstarting rule: " << g.start << "\n\n";

    for (auto const& rule : g.rules) {
        std::cout << rule.name << ": \n";
        std::cout << "\targs:\n";
        for (auto const& arg : rule.args) {
            std::cout << "\t\t" << arg.type << " " << arg.name << "\n";
        }
        std::cout << "\tattrs:\n";
        for (auto const& attr : rule.attrs) {
            std::cout << "\t\t" << attr.type << " " << attr.name << "\n";
        }
        std::cout << "\tvariants:\n";
        for (auto const& p : rule.variants) {
            std::cout << "\t\tproduction:\n";
            for (auto const& e : p) {
                std::visit(pfw::util::overloaded {
                    [](RuleRef const& r) { 
                        std::cout << "\t\t\tRuleRef " << r.name << "\n";
                        for (auto const& arg : r.args) {
                            std::cout << "\t\t\t\t" << arg.code << "\n";
                        }
                    },
                    [](Token const& t) { std::cout << "\t\t\tToken " << t.name << "\n"; },
                    [](Action const& a) { std::cout << "\t\t\tAction " << a.code << "\n"; },
                }, e);
            }
        }
    }

    std::cout << "tokens:\n";
    for (auto const& [k, v] : tokens_parser.map) {
        std::cout << k << " " << v << "\n";
    }

    Generator gen(g, std::move(tokens_parser.map), std::move(tokens_parser.skip_predicate), std::string(ns), std::string(out));
    gen.GenerateToken();
    gen.GenerateLexer();
    gen.GenerateAST();
    gen.GenerateParser();
}
