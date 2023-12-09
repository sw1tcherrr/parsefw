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
using NtNode = NonterminalNode<Node>;
using TNode = TokenNode<Token, Node>;

using Base = LangNodeBase<Node, NtNode, TNode>;

struct Node : Base,
              pfw::graphviz::GraphvizNode<Node> {
    using Base::LangNodeBase;
};

}  // namespace language::kotlin_func::ast