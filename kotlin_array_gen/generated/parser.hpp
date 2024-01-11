#pragma once

#include <tl/expected.hpp>
#include <format>

#include <pfw/parser_base.hpp>
#include <pfw/util.hpp>

#include "token.hpp"
#include "lexer.hpp"
#include "AST.hpp"

namespace kotlin_array {

template <std::bidirectional_iterator I>
struct Parser : pfw::ParserBase<I, Lexer<I>, Token> {
	private:
	using Base = pfw::ParserBase<I, Lexer<I>, Token>;
	using Base::NextToken, Base::cur_token;
	
	public:
	Parser(I begin, I end) : Base(std::move(begin), std::move(end)) {
	}
	
	template <typename T>
	using Result = tl::expected<T, std::string>;
	
	Result<Node> Parse() {
		NextToken();
		auto res = program();
		PFW_TRY(res)
		return Node(res.value());
	}
	
	private:
	
	Result<programNode> program() {
		programNode _0;
		if (this->template Expect<VAR>()) {
			auto res1 = declaration();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			PFW_TRY(this->template Expect<END>())
			auto _2 = _TokenNode(cur_token.value());
			_0.AddChild(_2);
			NextToken();
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<declarationNode> declaration() {
		declarationNode _0;
		if (this->template Expect<VAR>()) {
			PFW_TRY(this->template Expect<VAR>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = variableList();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			PFW_TRY(this->template Expect<SEMICOLON>())
			auto _3 = _TokenNode(cur_token.value());
			_0.AddChild(_3);
			NextToken();
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<variableListNode> variableList() {
		variableListNode _0;
		if (this->template Expect<ID>()) {
			auto res1 = variable();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			auto res2 = maybeListTail();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<maybeListTailNode> maybeListTail() {
		maybeListTailNode _0;
		if (this->template Expect<COMMA>()) {
			PFW_TRY(this->template Expect<COMMA>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = variableList();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			return _0;
		}
		if (this->template Expect<SEMICOLON>()) {
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<variableNode> variable() {
		variableNode _0;
		if (this->template Expect<ID>()) {
			PFW_TRY(this->template Expect<ID>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			PFW_TRY(this->template Expect<COLON>())
			auto _2 = _TokenNode(cur_token.value());
			_0.AddChild(_2);
			NextToken();
			
			PFW_TRY(this->template Expect<ID>())
			auto _3 = _TokenNode(cur_token.value());
			_0.AddChild(_3);
			NextToken();
			
			PFW_TRY(this->template Expect<LANGLE>())
			auto _4 = _TokenNode(cur_token.value());
			_0.AddChild(_4);
			NextToken();
			
			auto res5 = type();
			PFW_TRY(res5)
			auto _5 = res5.value();
			_0.AddChild(_5);
			
			PFW_TRY(this->template Expect<RANGLE>())
			auto _6 = _TokenNode(cur_token.value());
			_0.AddChild(_6);
			NextToken();
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<typeNode> type() {
		typeNode _0;
		if (this->template Expect<ID>()) {
			PFW_TRY(this->template Expect<ID>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
};

} // namespace kotlin_array
