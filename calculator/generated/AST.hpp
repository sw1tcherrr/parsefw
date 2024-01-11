#pragma once

#include <pfw/AST.hpp>
#include <pfw/graphviz.hpp>
#include "token.hpp"

namespace calc {

struct Node;

template <typename LangNode>
struct exprNodeT : pfw::ast::NonterminalNode<LangNode> {
	exprNodeT() : pfw::ast::NonterminalNode<LangNode>("expr") {
	}
	
	int val;
};

template <typename LangNode>
struct exprTailNodeT : pfw::ast::NonterminalNode<LangNode> {
	exprTailNodeT() : pfw::ast::NonterminalNode<LangNode>("exprTail") {
	}
	
	int val;
};

template <typename LangNode>
struct termNodeT : pfw::ast::NonterminalNode<LangNode> {
	termNodeT() : pfw::ast::NonterminalNode<LangNode>("term") {
	}
	
	int val;
};

template <typename LangNode>
struct termTailNodeT : pfw::ast::NonterminalNode<LangNode> {
	termTailNodeT() : pfw::ast::NonterminalNode<LangNode>("termTail") {
	}
	
	int val;
};

template <typename LangNode>
struct factorNodeT : pfw::ast::NonterminalNode<LangNode> {
	factorNodeT() : pfw::ast::NonterminalNode<LangNode>("factor") {
	}
	
	int val;
};

template <typename LangNode>
struct factorTailNodeT : pfw::ast::NonterminalNode<LangNode> {
	factorTailNodeT() : pfw::ast::NonterminalNode<LangNode>("factorTail") {
	}
	
	int val;
};

template <typename LangNode>
struct atomNodeT : pfw::ast::NonterminalNode<LangNode> {
	atomNodeT() : pfw::ast::NonterminalNode<LangNode>("atom") {
	}
	
	int val;
};

using exprNode = exprNodeT<Node>;
using exprTailNode = exprTailNodeT<Node>;
using termNode = termNodeT<Node>;
using termTailNode = termTailNodeT<Node>;
using factorNode = factorNodeT<Node>;
using factorTailNode = factorTailNodeT<Node>;
using atomNode = atomNodeT<Node>;
using _TokenNode = pfw::ast::TokenNode<Token, Node>;
using _NtNode = pfw::ast::NonterminalNode<Node>;

using Base = pfw::ast::LangNodeBase<Node, exprNode, exprTailNode, termNode, termTailNode, factorNode, factorTailNode, atomNode, _TokenNode>;

struct Node : Base, pfw::graphviz::GraphvizNode<Node> {
	using Base::Base;
};

} // namespace calc
