#pragma once

#include <concepts>
#include <iterator>
#include <optional>

#include "token_base.hpp"
#include "util.hpp"

namespace pfw {

template<std::bidirectional_iterator I>
struct LexerBase {
    using ValueType = typename std::iterator_traits<I>::value_type;

    LexerBase(I begin, I end) : iter(std::move(begin)), end(std::move(end)) {}

    LexerBase(LexerBase const&) = delete;
    LexerBase& operator=(LexerBase const&) = delete;

protected:
    I iter;
    I end;

    template <std::predicate<std::_Bit_const_iterator::value_type> P>
    void Skip(P&& p) {
        while (Expect(std::forward<P>(p))) {
            Consume();
        }
    }

    ValueType Expect(ValueType c) {
        return c == Peek();
    }

    template<std::predicate<std::_Bit_const_iterator::value_type> P>
    bool Expect(P&& p) {
        return std::invoke(std::forward<P>(p), Peek());
    }

    ValueType Peek() {
        if (iter == end) { return 0; }
        return *iter;
    }

    ValueType Consume() {
        return *(iter++);
    }

    void Consume(size_t n) {
        std::advance(iter, n);
    }
};

} // namespace parsefw