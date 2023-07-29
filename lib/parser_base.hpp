#pragma once

#include <variant>
#include "lexer_base.hpp"

namespace parsefw {

template<std::bidirectional_iterator I, typename Lexer, typename Token>
struct parser_base {
    parser_base(I begin, I end) : lex(std::move(begin), std::move(end)) {}

    parser_base(parser_base const&) = delete;
    parser_base& operator=(parser_base const&) = delete;

protected:
    Token cur_token;
    Lexer lex;

    void next_token() {
        cur_token = lex.next_token();
    }

    template <typename T>
    bool expect() {
        return std::holds_alternative<T>(cur_token);
    }

    template <typename T, std::predicate<T> P>
    bool expect(P&& p) {
        auto t = std::get_if<T>(&cur_token);
        return t && std::invoke(std::forward<P>(p), *t);
    }
};

} // namespace parsefw