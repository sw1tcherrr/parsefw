#pragma once

#include <concepts>
#include <string>

namespace pfw {
struct Eof {};
}  // namespace pfw

namespace pfw::token {

template <typename T>
    requires std::integral<T> || std::floating_point<T>
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

template <std::derived_from<String> Token>
std::string_view GetStringValue(Token const& t) {
    return t.string_value;
}

struct Exact : String {};

struct Variable : String {};

std::string_view GetStringValue(Eof const& t) {
    return "";
}

#define PFW_MAKE_TOKEN_TYPE(...) std::variant<pfw::Eof, __VA_ARGS__>

}  // namespace pfw::token