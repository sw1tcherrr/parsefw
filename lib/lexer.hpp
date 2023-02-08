#pragma once

#include <concepts>
#include <iterator>
#include <optional>

#include "token.hpp"
#include "util.hpp"

namespace parsefw {

using namespace parsefw::tokens;

// todo lexer_base (skip_spaces, peek, consume)
template<std::input_iterator I>
struct lexer {
    lexer(I begin, I end) : iter(std::move(begin)), end(std::move(end)) {}

    lexer(lexer const&) = delete;
    lexer& operator=(lexer const&) = delete;

    token next_token() {
        using util::operator|;
        skip_spaces();

        return parse_keyword_or_id() |
               [&] { return parse_operator_or_simples() |
                          [&] { return parse_number() |
                                [] { return eof{}; };};};
    }

private:
    I iter;
    I end;

    //using Traits::is_space, Traits::is_simple, Traits::is_keyword, Traits::is_id_start, Traits::is_id_part;

    void skip_spaces() {
        while (std::isspace(peek())) {
            consume();
        }
    }

    std::optional<token> parse_number() {
        return std::nullopt; // todo
    }

    std::optional<token> parse_operator_or_simples() { // todo
        PFW_TRY(expect(is_simple))
        return {token{simple(consume())}};
    }

    std::optional<token> parse_keyword_or_id() {
        PFW_TRY(expect(is_id_start))
        std::string res;
        res.push_back(consume());
        while (expect(is_id_part)) {
            res.push_back(consume());
        }
        if (keywords.contains(res)) {
            return {token{keyword{std::move(res)}}};
        }
        return {token{id{std::move(res)}}};
    }

    bool expect(char c) {
        return c == peek();
    }

    template<std::predicate<char> F>
    bool expect(F &&f) {
        return f(peek());
    }

    char peek() {
        if (iter == end) { return 0; }
        return *iter;
    }

    char consume() {
        return *(iter++);
    }
};

} // namespace parsefw