#pragma once
#include <variant>
#include <concepts>
#include <cassert>
#include "../lib/AST.hpp"
#include "../lib/graphviz.hpp"
#include "token.hpp"

namespace language::kotlin_func::AST {
using namespace parsefw::AST;

struct node;
using base = lang_node_base<node, token_node<token>, nonterminal_node<node>>;

struct node : base, parsefw::graphviz::graphviz_node<node> {
    using base::base;
};

}