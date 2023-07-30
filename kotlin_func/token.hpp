#pragma once

#include <variant>
#include <array>
#include <unordered_set>
#include <string>
#include "../lib/util.hpp"
#include "../lib/token_base.hpp"


namespace language::kotlin_func {

namespace x = parsefw::token; // todo rename

struct ID : x::variable     { static constexpr std::string_view pattern = R"([a-zA-Z_][\w-]*)"; }; // needs concrete string value
struct FUN : x::exact    { static constexpr std::string_view pattern = R"(fun)"; }; // todo dont store string_value if it is equal to pattern
struct LPAREN : x::exact { static constexpr std::string_view pattern = R"(\()"; }; // todo store precompiled regex (std is not constexpr, check ctre)
struct RPAREN : x::exact { static constexpr std::string_view pattern = R"(\))"; };
struct LANGLE : x::exact { static constexpr std::string_view pattern = R"(<)"; };
struct RANGLE : x::exact { static constexpr std::string_view pattern = R"(>)"; };
struct COLON : x::exact  { static constexpr std::string_view pattern = R"(:)"; };
struct COMMA : x::exact  { static constexpr std::string_view pattern = R"(,)"; };

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
            [&](const auto& x) { os << std::decay_t<decltype(x)>::pattern << " : " << get_string_value(x) << "\n"; },
    }, t);
    return os;
}

} // namespace language::kotlin_func