#include <cctype>
#include <string>
#include <unordered_map>
#include <format>
#include <iostream>

#include "generator.hpp"
#include "rule.hpp"
#include "grammar.hpp"

int main() {
    auto e = Rule{
        "E", 
        Inherits{},
        Synts{Attribute{"int", "val"}},
        Variants{
            Production{
                RuleRef{"T", {}},
                RuleRef{"Ep", {Arg{"_1.val"}}},
                Action{"_0.val = _2.val;"}
            }
        }
    };
    auto ep = Rule{
        "Ep", 
        Inherits{Attribute{"int", "acc"}},
        Synts{Attribute{"int", "val"}},
        Variants{
            Production{
                Token{"PLUS"}, 
                RuleRef{"T", {}},
                RuleRef{"Ep", {Arg{"acc + _2.val"}}},
                Action{"_0.val = _3.val;"},
            },
            Production{
                Action{"_0.val = acc;"}
            }
        }, 
    };
    auto t = Rule{
        "T",
        Inherits{},
        Synts{Attribute{"int", "val"}},
        Variants{
            Production{
                Token{"LPAREN"}, 
                RuleRef{"E", {}}, 
                Token{"RPAREN"},
                Action{"_0.val = _2.val;"}
            },
            Production{
                Token{"NUM"},
                Action{"_0.val = std::atoi(_1.GetStringValue().data());"}
            }
        },
    };

    std::unordered_map<std::string, Rule> map = {{"E", e}, {"Ep", ep}, {"T", t}};

    Grammar g(std::move(map), "E");
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

    std::unordered_map<std::string, std::string> tokens = {{"PLUS", R"(\+)"}, {"LPAREN", R"(\()"}, {"RPAREN", R"(\))"}, {"NUM", "[0-9]+"}}; 
    Generator gen(g, tokens, "[](unsigned char c) { return std::isspace(c); }", "calc");
    gen.GenerateToken();
    gen.GenerateLexer();
    gen.GenerateAST();
    gen.GenerateParser();
}