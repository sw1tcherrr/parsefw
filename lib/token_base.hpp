#pragma once

#include <string>
#include <concepts>

namespace parsefw {
    struct eof {};
}

namespace parsefw::token {

template <typename T> requires std::integral<T> || std::floating_point<T>
struct numeric {
    T numeric_value;
};

template <typename T, std::derived_from<numeric<T>> Token>
T get_numeric_value(Token const& t) {
    return t.numeric_value;
}

struct string {
    std::string string_value;
};

struct exact : string {};

template <std::derived_from<exact> Token>
std::string get_string_value(Token const& t) {
//    return std::string(Token::pattern);
    return t.string_value;
}

struct variable : string {};

template <std::derived_from<variable> Token>
std::string get_string_value(Token const& t) {
    return t.string_value;
}

std::string get_string_value(eof const& t) {
    return "";
}

#define PFW_MAKE_TOKEN_TYPE(...) std::variant<parsefw::eof, __VA_ARGS__>

} // namespace parsefw::token