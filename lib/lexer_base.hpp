#pragma once

#include <concepts>
#include <iterator>
#include <optional>

#include "token_base.hpp"
#include "util.hpp"

namespace parsefw {

template<std::bidirectional_iterator I>
struct lexer_base {
    using value_type = std::iterator_traits<I>::value_type;

    lexer_base(I begin, I end) : iter(std::move(begin)), end(std::move(end)) {}

    lexer_base(lexer_base const&) = delete;
    lexer_base& operator=(lexer_base const&) = delete;

protected:
    I iter;
    I end;

    template <std::predicate<value_type> P>
    void skip(P&& p) {
        while (expect(std::forward<P>(p))) {
            consume();
        }
    }

    bool expect(value_type c) {
        return c == peek();
    }

    template<std::predicate<value_type> P>
    bool expect(P&& p) {
        return std::invoke(std::forward<P>(p), peek());
    }

    value_type peek() {
        if (iter == end) { return 0; }
        return *iter;
    }

    value_type consume() {
        return *(iter++);
    }

    void consume(size_t n) {
        std::advance(iter, n);
    }
};

} // namespace parsefw