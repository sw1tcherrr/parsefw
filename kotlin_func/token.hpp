#pragma once

#include <array>
#include <ctll/fixed_string.hpp>
#include <string>
#include <unordered_set>
#include <variant>
#include <ostream>

#include "../lib/token_base.hpp"
#include "../lib/util.hpp"

namespace language::kotlin_func {

namespace x = pfw::token;  // todo rename

// todo: wrap in macro, which would also define pattern as static constexpr string_view
struct ID : x::Variable  { static constexpr ctll::fixed_string kPattern = R"([a-zA-Z_][\-\w]*)"; };
struct FUN : x::Exact    { static constexpr ctll::fixed_string kPattern = R"(fun)"; };
struct LPAREN : x::Exact { static constexpr ctll::fixed_string kPattern = R"(\()"; };
struct RPAREN : x::Exact { static constexpr ctll::fixed_string kPattern = R"(\))"; };
struct LANGLE : x::Exact { static constexpr ctll::fixed_string kPattern = R"(<)"; };
struct RANGLE : x::Exact { static constexpr ctll::fixed_string kPattern = R"(>)"; };
struct COLON : x::Exact  { static constexpr ctll::fixed_string kPattern = R"(:)"; };
struct COMMA : x::Exact  { static constexpr ctll::fixed_string kPattern = R"(,)"; };

using Token = PFW_MAKE_TOKEN_TYPE(ID, FUN, LPAREN, RPAREN, LANGLE, RANGLE, COLON, COMMA);

std::ostream& operator<<(std::ostream& os, Token const& t) {
    std::visit(pfw::util::overloaded {
            [&](pfw::Eof) { os << "EOF\n"; },
            [&](const auto& x) { os << x::GetStringValue(x) << "\n"; },
    }, t);
    return os;
}

}  // namespace language::kotlin_func