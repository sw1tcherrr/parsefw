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
		auto res = expr();
		PFW_TRY(res)
		return Node(res.value());
	}
	
	private:
	
	Result<exprNode> expr() {
		exprNode _0;
		if (this->template Expect<LPAREN>() || this->template Expect<NUM>()) {
			auto res1 = term();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			auto res2 = exprTail(_1.val);
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			_0.val = _2.val;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<exprTailNode> exprTail(int acc) {
		exprTailNode _0;
		if (this->template Expect<PLUS>()) {
			PFW_TRY(this->template Expect<PLUS>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = term();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			auto res3 = exprTail(acc + _2.val);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<MINUS>()) {
			PFW_TRY(this->template Expect<MINUS>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = term();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			auto res3 = exprTail(acc - _2.val);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<END>() || this->template Expect<RPAREN>()) {
			_0.val = acc;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<termNode> term() {
		termNode _0;
		if (this->template Expect<LPAREN>() || this->template Expect<NUM>()) {
			auto res1 = factor();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			auto res2 = termTail(_1.val);
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			_0.val = _2.val;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<termTailNode> termTail(int acc) {
		termTailNode _0;
		if (this->template Expect<MUL>()) {
			PFW_TRY(this->template Expect<MUL>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = factor();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			auto res3 = termTail(acc * _2.val);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<DIV>()) {
			PFW_TRY(this->template Expect<DIV>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = factor();
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			auto res3 = termTail(acc / _2.val);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<MINUS>() || this->template Expect<PLUS>() || this->template Expect<END>() || this->template Expect<RPAREN>()) {
			_0.val = acc;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<factorNode> factor() {
		factorNode _0;
		if (this->template Expect<LPAREN>() || this->template Expect<NUM>()) {
			auto res1 = atom();
			PFW_TRY(res1)
			auto _1 = res1.value();
			_0.AddChild(_1);
			
			auto res2 = factorTail(_1.val);
			PFW_TRY(res2)
			auto _2 = res2.value();
			_0.AddChild(_2);
			
			_0.val = _2.val;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<factorTailNode> factorTail(int acc) {
		factorTailNode _0;
		if (this->template Expect<BANG>()) {
			PFW_TRY(this->template Expect<BANG>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			 int fact = 1; 
                                                for (int i = 1; i <= acc; ++i) {
                                                    fact *= i;
                                                }
                                              
			
			auto res3 = factorTail(fact);
			PFW_TRY(res3)
			auto _3 = res3.value();
			_0.AddChild(_3);
			
			_0.val = _3.val;
			
			return _0;
		}
		if (this->template Expect<DIV>() || this->template Expect<MUL>() || this->template Expect<END>() || this->template Expect<PLUS>() || this->template Expect<MINUS>() || this->template Expect<RPAREN>()) {
			_0.val = acc;
			
			return _0;
		}
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
	Result<atomNode> atom() {
		atomNode _0;
		if (this->template Expect<LPAREN>()) {
			PFW_TRY(this->template Expect<LPAREN>())
			auto _1 = _TokenNode(cur_token.value());
			_0.AddChild(_1);
			NextToken();
			
			auto res2 = expr();
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
		
		PFW_TRY(cur_token)
		return tl::unexpected(std::format("Unexpected token {}\n", cur_token.value()));
	}
	
};

} // namespace calc
