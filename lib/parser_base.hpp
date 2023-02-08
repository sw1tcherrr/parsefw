#pragma once

#include "lexer.hpp"

namespace parsefw {

template<std::input_iterator I>
struct parser_base {
    parser_base(I begin, I end) : lex(std::move(begin), std::move(end)) {}

    parser_base(parser_base const&) = delete;
    parser_base& operator=(parser_base const&) = delete;

protected:
    lexer<I> lex;
    token cur_token;

    void next_token() {
        cur_token = lex.next_token();
    }

    bool expect_eof() {
        return std::holds_alternative<tokens::eof>(cur_token);
    }

    bool expect_simple(simple expected) {
        auto s = std::get_if<tokens::simple>(&cur_token);
        return s && *s == expected;
    }

    bool expect_keyword(std::string const &name) {
        auto k = std::get_if<tokens::keyword>(&cur_token);
        return k && k->name == name;
    }

    bool expect_id() {
        return std::holds_alternative<tokens::id>(cur_token);
    }
};

} // namespace parsefw