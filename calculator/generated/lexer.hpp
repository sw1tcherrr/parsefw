#pragma once

#include <concepts>
#include <ctre.hpp>
#include <stdexcept>
#include <string_view>
#include <tl/expected.hpp>

#include <pfw/lexer_base.hpp>
#include <pfw/token_base.hpp>
#include "token.hpp"

namespace calc {

template <std::contiguous_iterator I>
struct Lexer : pfw::LexerBase<I> {
	private:
	using Base = pfw::LexerBase<I>;
	using Base::iter, Base::end;
	
	public:
	Lexer(I begin, I end) : Base(std::move(begin), std::move(end)) {
	}
	tl::expected<Token, std::string> NextToken() {
		Base::Skip([](unsigned char c) { return std::isspace(c); });
		
		std::optional<Token> best_token;
		{
			auto res = Parse<NUM>();
			if (res && (!best_token || std::visit(pfw::token::GetStringValue, res.value()).size() > std::visit(pfw::token::GetStringValue, best_token.value()).size())) {
				best_token = res;
			}
		}
		
		{
			auto res = Parse<RPAREN>();
			if (res && (!best_token || std::visit(pfw::token::GetStringValue, res.value()).size() > std::visit(pfw::token::GetStringValue, best_token.value()).size())) {
				best_token = res;
			}
		}
		
		{
			auto res = Parse<LPAREN>();
			if (res && (!best_token || std::visit(pfw::token::GetStringValue, res.value()).size() > std::visit(pfw::token::GetStringValue, best_token.value()).size())) {
				best_token = res;
			}
		}
		
		{
			auto res = Parse<PLUS>();
			if (res && (!best_token || std::visit(pfw::token::GetStringValue, res.value()).size() > std::visit(pfw::token::GetStringValue, best_token.value()).size())) {
				best_token = res;
			}
		}
		
		if (!best_token) {
			best_token = Parse<pfw::token::END>();
		}
		
		if (!best_token) {
			return tl::unexpected(std::format("Can't parse any token on line {} at position {}", Base::Line(), Base::Position()));
		}
		
		Base::Consume(std::visit(pfw::token::GetStringValue, best_token.value()).size());
		return best_token.value();
	}
	
	private:
	
	template <std::derived_from<pfw::token::TokenBase> TokenType>
	std::optional<Token> Parse() {
		auto match = ctre::starts_with<TokenType::kPattern>(iter, end);
		if (match) {
			TokenType res(std::string_view(iter, iter + match.size()), Base::Line(), Base::Position());
			return {Token{std::move(res)}};
		}
		return std::nullopt;
	}
	
	template<>
	std::optional<Token> Parse<pfw::token::END>() {
		if (iter == end) {
			return {pfw::token::END("", Base::Line(), Base::Position())};
		}
		return std::nullopt;
	}
};

} // namespace calc
