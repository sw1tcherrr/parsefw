#pragma once

#include <pfw/token_base.hpp>

namespace calc {

PFW_TOKEN(PLUS, R"(\+)")
PFW_TOKEN(MINUS, R"(\-)")
PFW_TOKEN(MUL, R"(\*)")
PFW_TOKEN(DIV, R"(\/)")
PFW_TOKEN(LPAREN, R"(\()")
PFW_TOKEN(RPAREN, R"(\))")
PFW_TOKEN(BANG, R"(!)")
PFW_TOKEN(NUM, R"([0-9]+)")
using END = pfw::token::END;

using Token = pfw::token::TokenType<PLUS,MINUS,MUL,DIV,LPAREN,RPAREN,BANG,NUM>;

} // namespace calc
