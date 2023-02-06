#pragma once

#include "lexer.hpp"

namespace parsefw {

template<std::input_iterator I>
struct parser_base {
    parser_base(I begin, I end) : lex(std::move(begin), std::move(end)) {}

protected:
    lexer<I> lex;
    token cur_token;

    void next_token() {
        cur_token = lex.next_token();
    }

    bool expect_eof() {
        auto e = std::get_if<eof>(&cur_token);
        return e;
    }

    bool expect_simple(simple expected) {
        auto s = std::get_if<simple>(&cur_token);
        return s && *s == expected;
    }

    bool expect_keyword(std::string const &name) {
        auto k = std::get_if<keyword>(&cur_token);
        return k && k->name == name;
    }

    bool expect_id() {
        auto i = std::get_if<id>(&cur_token);
        return i;
    }
};

} // namespace parsefw