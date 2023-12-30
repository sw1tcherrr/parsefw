#pragma once

#include <string>
#include <variant>
#include <vector>

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

using RuleElement = std::variant<RuleRef, Token, Action>;
using Production  = std::vector<RuleElement>;
using Variants    = std::vector<Production>;
using Synts       = std::vector<Attribute>;
using Inherits    = std::vector<Attribute>;

struct Rule {
    std::string name;
    Inherits args;
    Synts attrs;
    Variants variants;
};