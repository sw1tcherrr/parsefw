#pragma once

#include <pfw/token_base.hpp>

namespace calc {

PFW_TOKEN(NUM, R"([0-9]+)")
PFW_TOKEN(RPAREN, R"(\))")
PFW_TOKEN(LPAREN, R"(\()")
PFW_TOKEN(PLUS, R"(\+)")
using END = pfw::token::END;

using Token = pfw::token::TokenType<NUM,RPAREN,LPAREN,PLUS>;

} // namespace calc
