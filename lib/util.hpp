#pragma once

#include <functional>
#include <iostream>
#include <optional>

namespace pfw::util {

// or_else for std::optional

//      <|> from Alternative, but the second argument is wrapped in lambda for laziness
//      (|) :: Maybe a -> (void -> Maybe a) -> Maybe a
//		(Just x) | func = Just x
//		Nothing  | func = func()
template <typename T, typename F>
std::optional<T> operator|(std::optional<T> opt, F&& func) {
    return opt ? opt : std::invoke(std::forward<F>(func));
}

//      fromMaybe, but the second argument is wrapped in lambda for laziness
//      (|=) :: Maybe a -> (void -> a) -> a
//      (Just x) |= func = x
//      Nothing  |= func = func()
template <typename T, typename F>
T operator|=(std::optional<T> opt, F&& func) {
    return opt ? *opt : std::invoke(std::forward<F>(func));
}

#define PFW_LAZY(func) [&] { return func(); }

// helper for visiting

template <typename... Ts>
struct overloaded : Ts... {  // NOLINT
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// instead of exceptions

#define PFW_TRY(x)                                        \
    if (!(x)) [[unlikely]] {                              \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        return std::nullopt;                              \
    }

}  // namespace pfw::util