#pragma once

#include<optional>

namespace parsefw::util {

// or_else for std::optional

template<typename T, typename F>
T operator|(std::optional<T> opt, F &&func) {
    return opt ? *opt : func();
}

// helper for visiting

template<typename... Ts>
struct overloaded : Ts ... {
    using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;


// instead of exceptions

#define PFW_TRY(x) if (!(x)) [[unlikely]] { std::cout << __FILE__ << ":" << __LINE__ << "\n"; return std::nullopt; }

} // namespace parsefw::util