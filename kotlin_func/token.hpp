#pragma once

#include <array>
#include <ctll/fixed_string.hpp>
#include <ostream>
#include <string>
#include <unordered_set>
#include <variant>

#include "../lib/token_base.hpp"
#include "../lib/util.hpp"

namespace language::kotlin_func {

PFW_TOKEN(ID,     Variable, R"([a-zA-Z_][\-\w]*)")
PFW_TOKEN(FUN,    Exact, R"(fun)")
PFW_TOKEN(LPAREN, Exact, R"(\()")
PFW_TOKEN(RPAREN, Exact, R"(\))")
PFW_TOKEN(LANGLE, Exact, R"(<)")
PFW_TOKEN(RANGLE, Exact, R"(>)")
PFW_TOKEN(COLON,  Exact, R"(:)")
PFW_TOKEN(COMMA,  Exact, R"(,)")

using Token = PFW_MAKE_TOKEN_TYPE(ID, FUN, LPAREN, RPAREN, LANGLE, RANGLE, COLON, COMMA);

std::ostream& operator<<(std::ostream& os, Token const& t) {
    std::visit(pfw::util::overloaded{
                   [&](pfw::Eof) { os << "EOF\n"; },
                   [&](const auto& x) { os << pfw::token::GetStringValue(x) << "\n"; },
               },
               t);
    return os;
}

}  // namespace language::kotlin_func