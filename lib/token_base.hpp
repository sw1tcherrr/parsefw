#pragma once

#include <concepts>
#include <format>
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
};

std::string_view GetStringValue(TokenBase const& t) {
    return t.string_value;
}

template <typename T>
    requires std::integral<T> || std::floating_point<T>
struct Numeric {
    T numeric_value;
};

template <typename T, std::derived_from<Numeric<T>> Token>
T GetNumericValue(Token const& t) {
    return t.numeric_value;
}

#define PFW_TOKEN(NAME, PATTERN, ...)  \
struct NAME : ::pfw::token::TokenBase, ##__VA_ARGS__ { \
    static constexpr ctll::fixed_string kPattern = PATTERN; \
    static constexpr std::string_view kPatternStr = PATTERN; \
    static constexpr std::string_view kName = #NAME;\
    using Base = ::pfw::token::TokenBase; \
    using Base::TokenBase; \
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