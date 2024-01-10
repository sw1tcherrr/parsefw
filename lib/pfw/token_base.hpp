#pragma once

#include <concepts>
#include <format>
#include <iostream>
#include <string>
#include <variant>
#include <ctll/fixed_string.hpp>

namespace pfw::token {

struct TokenBase {
    std::string_view string_value;
    size_t line;
    size_t position;

    explicit TokenBase(std::string_view string_value = "", size_t line = 0, size_t position = 0) 
    : string_value(string_value), line(line), position(position) {
    }

    bool operator==(TokenBase const& other) const {
        auto res = string_value == other.string_value;
        if (!res) {
            std::cerr << "Mismatch in " << string_value << " " << other.string_value << "\n";
        }
        return res;
    }
};

std::string_view GetStringValue(TokenBase const& t) {
    return t.string_value;
}

#define PFW_TOKEN(NAME, PATTERN)  \
struct NAME : ::pfw::token::TokenBase { \
    static constexpr ctll::fixed_string kPattern = PATTERN; \
    static constexpr std::string_view kPatternStr = PATTERN; \
    static constexpr std::string_view kName = #NAME;\
    using Base = ::pfw::token::TokenBase; \
    using Base::Base; \
};

PFW_TOKEN(END, "")

template <typename... Tokens>
using TokenType = std::variant<END, Tokens...>;

template <typename... Tokens>
std::ostream& operator<<(std::ostream& os, TokenType<Tokens...> const& t) {
    os << std::format("{}", t);
    return os;
}

}  // namespace pfw::token

namespace std {
template <typename... Tokens>
struct std::formatter<pfw::token::TokenType<Tokens...>> : std::formatter<std::string> {
    auto format(pfw::token::TokenType<Tokens...> const& token, std::format_context& ctx) const {
        std::string res = std::visit(
            [&]<std::derived_from<pfw::token::TokenBase> T>(T const& t) {
                return std::format("{} : `{}` on line {} at postion {}",
                    T::kName,
                    t.string_value,
                    t.line,
                    t.position);
        },
        token);
        return std::formatter<std::string>::format(res, ctx);
    }
};
} // namespace std