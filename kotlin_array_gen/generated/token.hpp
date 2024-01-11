#pragma once

#include <pfw/token_base.hpp>

namespace kotlin_array {

PFW_TOKEN(VAR, R"(var)")
PFW_TOKEN(ID, R"([a-zA-Z_][a-zA-Z_0-9]*)")
PFW_TOKEN(COLON, R"(:)")
PFW_TOKEN(SEMICOLON, R"(;)")
PFW_TOKEN(LANGLE, R"(<)")
PFW_TOKEN(RANGLE, R"(>)")
PFW_TOKEN(COMMA, R"(,)")
using END = pfw::token::END;

using Token = pfw::token::TokenType<VAR,ID,COLON,SEMICOLON,LANGLE,RANGLE,COMMA>;

} // namespace kotlin_array
