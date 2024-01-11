#pragma once

#include <string>
#include <variant>
#include <vector>

namespace pfw::gen {

struct Token {
    std::string name;
};

struct Action {
    std::string code;
};

struct Attribute {
    std::string type;
    std::string name;
};

struct Arg {
    std::string code;
};

struct RuleRef {
    std::string name;
    std::vector<Arg> args;
};

using ProductionElement = std::variant<RuleRef, Token, Action>;
using Production        = std::vector<ProductionElement>;
using Variants          = std::vector<Production>;
using Synts             = std::vector<Attribute>;
using Inherits          = std::vector<Attribute>;

struct Rule {
    std::string name;
    Inherits args;
    Synts attrs;
    Variants variants;
};

} // namespace pfw::gen

/*
Example:

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
*/