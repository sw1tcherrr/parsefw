#pragma once

#include <pfw/AST.hpp>
#include <pfw/graphviz.hpp>
#include "token.hpp"

namespace kotlin_array {

struct Node;
using NtNode = pfw::ast::NonterminalNode<Node>;
using TNode  = pfw::ast::TokenNode<Token, Node>;

using Base = pfw::ast::LangNodeBase<Node, NtNode, TNode>;

struct Node : Base,
              pfw::graphviz::GraphvizNode<Node> {
    using Base::Base;
};

} // namespace kotlin_array