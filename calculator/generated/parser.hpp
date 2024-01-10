#pragma once

#include <tl/expected.hpp>
#include <format>

#include <pfw/parser_base.hpp>
#include <pfw/util.hpp>

#include "token.hpp"
#include "lexer.hpp"
#include "AST.hpp"

namespace calc {

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
		auto res = E();
		PFW_TRY(res)
		return Node(res.value());
	}
	
	private:
	
	Result<TNode> T() {
		TNode _0;
		if (this->template Expect<LPAREN>()) {
			PFW_TRY(this->template Expect<LPAREN>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = E();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			PFW_TRY(this->template Expect<RPAREN>())
			auto _3 = _TokenNode(cur_token.value());
			_0.AddChild(_3);
			NextToken();
			
			_0.val = _2.val;
			
			return _0;
		}
		if (this->template Expect<NUM>()) {
			PFW_TRY(this->template Expect<NUM>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			_0.val = std::atoi(_1.GetStringValue().data());
			
			return _0;
		}
		return tl::unexpected(std::format("Unexpected token {}\n", this->cur_token.value()));
	}
	
	Result<EpNode> Ep(int acc) {
		EpNode _0;
		if (this->template Expect<PLUS>()) {
			PFW_TRY(this->template Expect<PLUS>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = T();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			auto res3 = Ep(acc + _2.val);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<RPAREN>() || this->template Expect<END>()) {
			_0.val = acc;
			
			return _0;
		}
		return tl::unexpected(std::format("Unexpected token {}\n", this->cur_token.value()));
	}
	
	Result<ENode> E() {
		ENode _0;
		if (this->template Expect<LPAREN>() || this->template Expect<NUM>()) {
			auto res1 = T();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			auto res2 = Ep(_1.val);
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			_0.val = _2.val;
			
			return _0;
		}
		return tl::unexpected(std::format("Unexpected token {}\n", this->cur_token.value()));
	}
	
};

} // namespace calc
