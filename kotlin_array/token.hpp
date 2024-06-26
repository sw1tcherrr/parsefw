#pragma once

#include <pfw/token_base.hpp>

namespace kotlin_array {

PFW_TOKEN(ID,        R"([a-zA-Z_][\w]*)")
PFW_TOKEN(VAR,       R"(var)")
PFW_TOKEN(LANGLE,    R"(<)")
PFW_TOKEN(RANGLE,    R"(>)")
PFW_TOKEN(COMMA,     R"(,)")
PFW_TOKEN(COLON,     R"(:)")
PFW_TOKEN(SEMICOLON, R"(;)")

using Token = pfw::token::TokenType<ID, VAR, LANGLE, RANGLE, COMMA, COLON, SEMICOLON>;

} // namespace kotlin_array