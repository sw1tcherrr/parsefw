#pragma once

#include <concepts>
#include <ctre.hpp>
#include <stdexcept>
#include <string_view>

#include "../lib/lexer_base.hpp"
#include "../lib/util.hpp"
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
                               | PFW_LAZY(Parse<pfw::token::END>);
                

        iter = start_pos;

        auto variable_res = Parse<ID>()
                                  | PFW_LAZY(Parse<pfw::token::END>);

        iter = start_pos;

        if (!exact_res && !variable_res) {
            throw std::runtime_error(std::format("Can't parse any token on line {} at position {}", this->lines.size() - 1, iter - this->lines.back())); 
            // todo don't throw
        }

        std::string_view ex_str = "";
        if (exact_res) {
            ex_str = std::visit(pfw::token::GetStringValue, exact_res.value());
        }

        std::string_view var_str = "";
        if (variable_res) {
            var_str = std::visit(pfw::token::GetStringValue, variable_res.value());
        }

        if (ex_str.size() >= var_str.size()) {
            Base::Consume(ex_str.size());
            return exact_res.value();
        } else {
            Base::Consume(var_str.size());
            return variable_res.value();
        }
    }

private:
    using Base::iter, Base::end;

    template <std::derived_from<pfw::token::TokenBase> TokenType>
    std::optional<Token> Parse() {
        auto match = ctre::starts_with<TokenType::kPattern>(iter, end);
        if (match) {
            TokenType res{pfw::token::TokenBase
                            {.line = this->lines.size() - 1,
                            .position = size_t(iter - this->lines.back()),
                            .string_value = std::string_view(iter, iter + match.size())}};
            Base::Consume(match.size());
            return {Token{std::move(res)}};
        }
        return std::nullopt;
    }

    template <>
    std::optional<Token> Parse<pfw::token::END>() {
        if (iter == end) {
            return {pfw::token::END{}};
        }
        return std::nullopt;
    }
};

}  // namespace language::kotlin_func