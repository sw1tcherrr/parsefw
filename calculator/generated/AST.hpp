#pragma once

#include <pfw/AST.hpp>
#include <pfw/graphviz.hpp>
#include "token.hpp"

namespace calc {

struct Node;

template <typename LangNode>
struct TNodeT : pfw::ast::NonterminalNode<LangNode> {
	TNodeT() : pfw::ast::NonterminalNode<LangNode>("T") {
	}
	
	int val;
};

template <typename LangNode>
struct EpNodeT : pfw::ast::NonterminalNode<LangNode> {
	EpNodeT() : pfw::ast::NonterminalNode<LangNode>("Ep") {
	}
	
	int val;
};

template <typename LangNode>
struct ENodeT : pfw::ast::NonterminalNode<LangNode> {
	ENodeT() : pfw::ast::NonterminalNode<LangNode>("E") {
	}
	
	int val;
};

using TNode = TNodeT<Node>;
using EpNode = EpNodeT<Node>;
using ENode = ENodeT<Node>;
using _TokenNode = pfw::ast::TokenNode<Token, Node>;
using _NtNode = pfw::ast::NonterminalNode<Node>;

using Base = pfw::ast::LangNodeBase<Node, TNode, EpNode, ENode, _TokenNode>;

struct Node : Base, pfw::graphviz::GraphvizNode<Node> {
	using Base::Base;
};

} // namespace calc
