#include "rule.hpp"
#include <string>
#include <unordered_map>
#include <format>

#include "../lib/token_base.hpp"

PFW_TOKEN(PLUS,   R"(+)")
PFW_TOKEN(LPAREN, R"(\()")
PFW_TOKEN(RPAREN, R"(\))")

int main() {
    auto e = Rule{
        "E", 
        Inherits{},
        Synts{Attribute{"int", "val"}},
        Variants{
            Production{
                RuleRef{"T", {}},
                RuleRef{"E'", {}}
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
                RuleRef{"Ep", {Arg{"acc + $1.val"}}},
                Action{"$0.val = $3.val;"},
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
                Action{"$0.val = $2.val;"}
            },
            Production{
                Token{R"([0-9]+)"},
                Action{"$0.val = std::atoi($1.GetStringValue());"}
            }
        },
    };

    std::unordered_map<std::string, Rule> map = {{"E", e}, {"Ep", ep}, {"T", t}};

    std::cout << std::format("Result {}({}) {{\n", map["Ep"].name, map["Ep"].args[0].type + " " + map["Ep"].args[0].name);
}