#pragma once

#include <string>
#include <concepts>

namespace pfw {
    struct Eof {};
}

namespace pfw::token {

template <typename T> requires std::integral<T> || std::floating_point<T>
struct Numeric {
    T numeric_value;
};

template <typename T, std::derived_from<Numeric<T>> Token>
T GetNumericValue(Token const& t) {
    return t.numeric_value;
}

struct String {
    std::string string_value;
};

struct Exact : String {};

template <std::derived_from<Exact> Token>
std::string GetStringValue(Token const& t) {
//    return std::string(Token::pattern);
    return t.string_value;
}

struct Variable : String {};

template <std::derived_from<Variable> Token>
std::string GetStringValue(Token const& t) {
    return t.string_value;
}

std::string GetStringValue(Eof const& t) {
    return "";
}

#define PFW_MAKE_TOKEN_TYPE(...) std::variant<pfw::Eof, __VA_ARGS__>

} // namespace parsefw::token