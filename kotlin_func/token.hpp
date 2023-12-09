#pragma once

#include <array>
#include <ctll/fixed_string.hpp>
#include <ostream>
#include <string>
#include <unordered_set>
#include <variant>

#include "../lib/token_base.hpp"

namespace language::kotlin_func {

PFW_TOKEN(ID,     R"([a-zA-Z_][\-\w]*)")
PFW_TOKEN(FUN,    R"(fun)")
PFW_TOKEN(LPAREN, R"(\()")
PFW_TOKEN(RPAREN, R"(\))")
PFW_TOKEN(LANGLE, R"(<)")
PFW_TOKEN(RANGLE, R"(>)")
PFW_TOKEN(COLON,  R"(:)")
PFW_TOKEN(COMMA,  R"(,)")

using Token = pfw::token::TokenType<ID, FUN, LPAREN, RPAREN, LANGLE, RANGLE, COLON, COMMA>;

}  // namespace language::kotlin_func