#pragma once
#include <cassert>
#include <concepts>
#include <variant>

#include "../lib/AST.hpp"
#include "../lib/graphviz.hpp"
#include "token.hpp"

namespace language::kotlin_func::ast {
using namespace pfw::ast;

struct Node;
using Base = LangNodeBase<Node, TokenNode<Token>, NonterminalNode<Node>>;

struct Node : Base, pfw::graphviz::GraphvizNode<Node> {
    using Base::LangNodeBase;
};

}  // namespace language::kotlin_func::ast