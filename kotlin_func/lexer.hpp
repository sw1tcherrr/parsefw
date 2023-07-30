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

        auto start_pos = iter;

        auto exact_res = parse<FUN>()
                         > std::bind(&lexer<I>::parse<LPAREN>, this) // мб замена лямбде, но все равно многословно => в макросе
                         > PFW_LAZY(parse<RPAREN>)
                         > PFW_LAZY(parse<LANGLE>)
                         > PFW_LAZY(parse<RANGLE>)
                         > PFW_LAZY(parse<COLON>)
                         > PFW_LAZY(parse<COMMA>)
                         >= [] { return token{eof{}}; };

        iter = start_pos;

        auto variable_res = parse<ID>() >= [] {return token{eof{}}; };

        iter = start_pos;

        std::string ex_str = std::visit([] (auto const& t){ return parsefw::token::get_string_value(t); }, exact_res);
        std::string var_str = std::visit([] (auto const& t){ return parsefw::token::get_string_value(t); }, variable_res);
        if (ex_str.size() >= var_str.size()) {
            base::consume(ex_str.size());
            return exact_res;
        } else {
            base::consume(var_str.size());
            return variable_res;
        }
    }

private:
    using base::iter, base::end;

//    template <std::derived_from<parsefw::token::exact> Token>
//    std::optional<token> parse() {
//        std::regex pattern(Token::pattern.data());
//        std::match_results<I> m;
//        std::regex_search(iter, end, m, pattern, std::regex_constants::match_continuous);
//        if (!m.empty()) {
//            base::consume(m[0].second - m[0].first); // problem if exact pattern contains regex escapes which make string_value longer
//            // todo: make this not real consume, remember start position
//            return {token{Token{}}}; // todo string_value not initialized
//        }
//        return {};
//    }

    template <std::derived_from<parsefw::token::string> Token>
    std::optional<token> parse() {
        std::regex pattern(Token::pattern.data());
        std::match_results<I> m;
        std::regex_search(iter, end, m, pattern, std::regex_constants::match_continuous);
        if (!m.empty()) {
            Token res{std::string(m[0].first, m[0].second)}; // todo понятнее
            base::consume(m[0].second - m[0].first);
            return {token{std::move(res)}};
        }
        return {};
    }

};

} // namespace language::kotlin_func