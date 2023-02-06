#pragma once

#include <variant>
#include <array>
#include <unordered_set>
#include <string>
#include "util.hpp"

namespace parsefw::tokens {

struct id {
    std::string name;
};

inline bool is_id_start(char c) {
    return c == '_' || c == '-' || std::isalpha(c);
}

inline bool is_id_part(char c) {
    return c == '_' || c == '-' || std::isalnum(c);
}

struct keyword {
    std::string name;
};

const inline std::unordered_set<std::string> keywords = {"fun"};

enum simple {
    LPAREN = '(',
    RPAREN = ')',
    LANGLE = '<',
    RANGLE = '>',
    COLON = ':',
    COMMA = ','
};

inline bool is_simple(char c) {
    switch (c) {
        case LPAREN:
        case RPAREN:
        case LANGLE:
        case RANGLE:
        case COLON:
        case COMMA:
            return true;
        default:
            return false;
    }
}

using eof = std::monostate;

using token = std::variant<eof, simple, keyword, id>;

std::ostream& operator<<(std::ostream& os, token const& t) {
    std::visit(util::overloaded {
        [&](eof) { os << "EOF\n"; },
        [&](simple s) { os << (char)s << "\t - simple\n"; },
        [&](keyword const& k) { os << k.name << "\t - keyword\n"; },
        [&](id const& i) { os << i.name << "\t - id\n"; }
    }, t);
    return os;
}

inline bool is_eof(token const& t) {
    return std::holds_alternative<eof>(t);
}

} // namespace parsefw