#pragma once

#include <string>
#include <concepts>

namespace parsefw {
    struct eof {};
}

namespace parsefw::token {

struct string {
    std::string string_value;
};

template <typename T> requires std::integral<T> || std::floating_point<T>
struct numeric {
    T numeric_value;
};

template <const char* Pattern>
struct pattern {
    static constexpr std::string_view pattern_ = Pattern;
};

#define PFW_MAKE_TOKEN_TYPE(...) std::variant<parsefw::eof, __VA_ARGS__>

} // namespace parsefw::token