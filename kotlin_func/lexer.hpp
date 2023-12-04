#pragma once

#include <concepts>
#include <ctre.hpp>

#include "../lib/lexer_base.hpp"
#include "token.hpp"

namespace language::kotlin_func {

using namespace pfw;

template <std::bidirectional_iterator I>
struct Lexer : pfw::LexerBase<I> {
    using Base = pfw::LexerBase<I>;

    Lexer(I begin, I end) : Base(std::move(begin), std::move(end)) {
    }

    Token NextToken() {
        using util::operator|;
        using util::operator|=;
        Base::Skip([](unsigned char c) { return std::isspace(c); });

        // бывают exact и regex
        // exact между собой отсортированы по длине по убыванию
        // сначала парсятся они цепочкой из | => res_exact
        // потом парсятся regex (записанные в виде грамматики, видимо, туда же)
        // не останавливаемся на первом сработавшем, а вызываем все, выбирамем самый длинный
        // res_regex сравниваем длину двух res и делаем consume наибольшей

        auto start_pos = iter;

        auto exact_res = Parse<FUN>()
                         | PFW_LAZY(Parse<LPAREN>)
                         | PFW_LAZY(Parse<RPAREN>)
                         | PFW_LAZY(Parse<LANGLE>)
                         | PFW_LAZY(Parse<RANGLE>)
                         | PFW_LAZY(Parse<COLON>)
                         | PFW_LAZY(Parse<COMMA>)
                         |= [] { return Token{Eof{}}; };

        iter = start_pos;

        auto variable_res = Parse<ID>() 
                            |= [] { return Token{Eof{}}; };

        iter = start_pos;

        auto ex_str = std::visit([](auto const& t) { return pfw::token::GetStringValue(t); }, exact_res);
        auto var_str = std::visit([](auto const& t) { return pfw::token::GetStringValue(t); }, variable_res);
        if (ex_str.size() >= var_str.size()) {
            Base::Consume(ex_str.size());
            return exact_res;
        } else {
            Base::Consume(var_str.size());
            return variable_res;
        }
    }

private:
    using Base::iter, Base::end;

    template <std::derived_from<pfw::token::String> TokenType>
    std::optional<Token> Parse() {
        auto match = ctre::starts_with<TokenType::kPattern>(iter, end);
        if (match) {
            TokenType res{pfw::token::String{.string_value = std::string_view(iter, iter + match.size())}};
            Base::Consume(match.size());
            return {Token{std::move(res)}};
        }
        return {};
    }
};

}  // namespace language::kotlin_func