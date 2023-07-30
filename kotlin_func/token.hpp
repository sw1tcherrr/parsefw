#pragma once

#include <array>
#include <string>
#include <unordered_set>
#include <variant>

#include "../lib/token_base.hpp"
#include "../lib/util.hpp"

namespace language::kotlin_func {

namespace x = pfw::token;  // todo rename

struct ID : x::Variable  { static constexpr std::string_view kPattern = R"([a-zA-Z_][\w-]*)"; }; // needs concrete string value
struct FUN : x::Exact    { static constexpr std::string_view kPattern = R"(fun)"; }; // todo dont store string_value if it is equal to pattern
struct LPAREN : x::Exact { static constexpr std::string_view kPattern = R"(\()"; }; // todo store precompiled regex (std is not constexpr, check ctre)
struct RPAREN : x::Exact { static constexpr std::string_view kPattern = R"(\))"; };
struct LANGLE : x::Exact { static constexpr std::string_view kPattern = R"(<)"; };
struct RANGLE : x::Exact { static constexpr std::string_view kPattern = R"(>)"; };
struct COLON : x::Exact  { static constexpr std::string_view kPattern = R"(:)"; };
struct COMMA : x::Exact  { static constexpr std::string_view kPattern = R"(,)"; };

using Token = PFW_MAKE_TOKEN_TYPE(ID, FUN, LPAREN, RPAREN, LANGLE, RANGLE, COLON, COMMA);

std::ostream& operator<<(std::ostream& os, Token const& t) {
    std::visit(pfw::util::overloaded {
            [&](pfw::Eof) { os << "EOF\n"; },
            [&](const auto& x) { os << std::decay_t<decltype(x)>::kPattern << " : " << x::GetStringValue(x) << "\n"; },
    }, t);
    return os;
}

}  // namespace language::kotlin_func