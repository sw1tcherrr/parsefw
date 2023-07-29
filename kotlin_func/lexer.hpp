#pragma once

#include <concepts>
#include <regex>

#include "../lib/lexer_base.hpp"
#include "token.hpp"

namespace language::kotlin_func {

using namespace parsefw;

template<std::bidirectional_iterator I>
struct lexer : parsefw::lexer_base<I> {
    using base = parsefw::lexer_base<I>;

    lexer(I begin, I end) : base(std::move(begin), std::move(end)) {}

    token next_token() {
        using util::operator>;
        using util::operator>=;
        base::skip([](unsigned char c) { return std::isspace(c); } );

        // бывают exact и regex
        // exact между собой отсортированы по длине по убыванию
        // сначала парсятся они цепочкой из | => res_exact
        // потом парсятся regex (записанные в виде грамматики, видимо, туда же)
        // не останавливаемся на первом сработавшем, а вызываем все, выбирамем самый длинный res_regex
        // сравниваем длину двух res и делаем consume наибольшей

         return parse<FUN>()
                > PFW_LAZY(parse_id)
                > std::bind(&lexer<I>::parse<LPAREN>, this) // мб замена лямбде, но все равно многословно => в макросе
                > PFW_LAZY(parse<RPAREN>)
                > PFW_LAZY(parse<LANGLE>)
                > PFW_LAZY(parse<RANGLE>)
                > PFW_LAZY(parse<COLON>)
                > PFW_LAZY(parse<COMMA>)
                >= [] { return token{eof{}}; }; // todo find operator with same priority as |
    }

private:
    using base::iter, base::end;

    template <typename T>
    std::optional<token> parse() {
        std::regex pattern(T::pattern.data());
        std::match_results<I> m;
        std::regex_search(iter, end, m, pattern, std::regex_constants::match_continuous);
        if (!m.empty()) {
            base::consume(T::pattern.size());
            return {token{T{}}}; // todo string_value not initialized
        }
        return {};
    }

    std::optional<token> parse_id() {
        std::regex pattern(ID::pattern.data());
        std::match_results<I> m;
        std::regex_search(iter, end, m, pattern, std::regex_constants::match_continuous);
        if (!m.empty()) {
            ID res{std::string(m[0].first, m[0].second)}; // todo понятнее
            base::consume(res.string_value.size());
            return {token{std::move(res)}};
        }
        return {};
    }

};

} // namespace language::kotlin_func