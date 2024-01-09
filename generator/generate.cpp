#include <string>
#include <unordered_map>
#include <format>
#include <iostream>

#include "rule.hpp"
#include "grammar.hpp"

// #include "../lib/token_base.hpp"

// PFW_TOKEN(PLUS,   R"(+)")
// PFW_TOKEN(LPAREN, R"(\()")
// PFW_TOKEN(RPAREN, R"(\))")

int main() {
    auto e = Rule{
        "E", 
        Inherits{},
        Synts{Attribute{"int", "val"}},
        Variants{
            Production{
                RuleRef{"T", {}},
                RuleRef{"Ep", {}}
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
                RuleRef{"Ep", {Arg{"acc + _1.val"}}},
                Action{"_0.val = _3.val;"},
            },
            Production{
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
                Action{"_0.val = std::atoi(_1.GetStringValue());"}
            }
        },
    };

    std::unordered_map<std::string, Rule> map = {{"E", e}, {"Ep", ep}, {"T", t}};
    //std::cout << std::format("Result {}({}) {{\n", map["Ep"].name, map["Ep"].args[0].type + " " + map["Ep"].args[0].name);

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
}