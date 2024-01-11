#pragma once

#include <pfw/AST.hpp>
#include <pfw/graphviz.hpp>
#include "token.hpp"

namespace kotlin_array {

struct Node;

template <typename LangNode>
struct programNodeT : pfw::ast::NonterminalNode<LangNode> {
	programNodeT() : pfw::ast::NonterminalNode<LangNode>("program") {
	}
	
};

template <typename LangNode>
struct declarationNodeT : pfw::ast::NonterminalNode<LangNode> {
	declarationNodeT() : pfw::ast::NonterminalNode<LangNode>("declaration") {
	}
	
};

template <typename LangNode>
struct variableListNodeT : pfw::ast::NonterminalNode<LangNode> {
	variableListNodeT() : pfw::ast::NonterminalNode<LangNode>("variableList") {
	}
	
};

template <typename LangNode>
struct maybeListTailNodeT : pfw::ast::NonterminalNode<LangNode> {
	maybeListTailNodeT() : pfw::ast::NonterminalNode<LangNode>("maybeListTail") {
	}
	
};

template <typename LangNode>
struct variableNodeT : pfw::ast::NonterminalNode<LangNode> {
	variableNodeT() : pfw::ast::NonterminalNode<LangNode>("variable") {
	}
	
};

template <typename LangNode>
struct typeNodeT : pfw::ast::NonterminalNode<LangNode> {
	typeNodeT() : pfw::ast::NonterminalNode<LangNode>("type") {
	}
	
};

using programNode = programNodeT<Node>;
using declarationNode = declarationNodeT<Node>;
using variableListNode = variableListNodeT<Node>;
using maybeListTailNode = maybeListTailNodeT<Node>;
using variableNode = variableNodeT<Node>;
using typeNode = typeNodeT<Node>;
using _TokenNode = pfw::ast::TokenNode<Token, Node>;
using _NtNode = pfw::ast::NonterminalNode<Node>;

using Base = pfw::ast::LangNodeBase<Node, programNode, declarationNode, variableListNode, maybeListTailNode, variableNode, typeNode, _TokenNode>;

struct Node : Base, pfw::graphviz::GraphvizNode<Node> {
	using Base::Base;
};

} // namespace kotlin_array
