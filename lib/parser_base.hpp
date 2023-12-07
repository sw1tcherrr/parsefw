#pragma once

#include <format>
#include <functional>
#include <string>
#include <tl/expected.hpp>
#include <variant>

namespace pfw {

template <std::bidirectional_iterator I, typename Lexer, typename Token>
struct ParserBase {
    ParserBase(I begin, I end) : lex(std::move(begin), std::move(end)) {
    }

    ParserBase(ParserBase const&) = delete;
    ParserBase& operator=(ParserBase const&) = delete;

protected:
    Token cur_token;
    Lexer lex;

    void NextToken() {
        cur_token = lex.NextToken();
    }

    template <typename T>
    tl::expected<std::monostate, std::string> Expect() {
        if (std::holds_alternative<T>(cur_token)) {
            return {};
        }
        return tl::unexpected(std::format("Expected {}, got {}", T::kName, cur_token));
    }

    // template <typename T, std::predicate<T> P>
    // bool Expect(P&& p) {
    //     auto t = std::get_if<T>(&cur_token);
    //     return t && std::invoke(std::forward<P>(p), *t);
    // }
};

}  // namespace pfw