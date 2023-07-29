#pragma once

#include <variant>
#include <array>
#include <unordered_set>
#include <string>
#include "../lib/util.hpp"
#include "../lib/token_base.hpp"


namespace language::kotlin_func {

namespace x = parsefw::token; // todo rename

struct ID : x::string     { static constexpr std::string_view pattern = R"([a-zA-Z_][\w-]*)"; }; // needs concrete string value
struct FUN : x::string    { static constexpr std::string_view pattern = R"(fun)"; }; // todo dont store string_value if it is equal to pattern
struct LPAREN : x::string { static constexpr std::string_view pattern = R"(\()"; }; // todo store precompiled regex (std is not constexpr, check ctre)
struct RPAREN : x::string { static constexpr std::string_view pattern = R"(\))"; };
struct LANGLE : x::string { static constexpr std::string_view pattern = R"(<)"; };
struct RANGLE : x::string { static constexpr std::string_view pattern = R"(>)"; };
struct COLON : x::string  { static constexpr std::string_view pattern = R"(:)"; };
struct COMMA : x::string  { static constexpr std::string_view pattern = R"(,)"; };

// possible optimization
/*enum simple {
    LPAREN = '(',
    RPAREN = ')',
    LANGLE = '<',
    RANGLE = '>',
    COLON = ':',
    COMMA = ','
};*/


using token = PFW_MAKE_TOKEN_TYPE(ID, FUN, LPAREN, RPAREN, LANGLE, RANGLE, COLON, COMMA);

std::ostream& operator<<(std::ostream& os, token const& t) {
    std::visit(parsefw::util::overloaded {
            [&](parsefw::eof) { os << "EOF\n"; },
            [&](const auto& x) { os << std::decay_t<decltype(x)>::pattern << " : " << x.string_value << "\n"; },
    }, t);
    return os;
}

} // namespace language::kotlin_func