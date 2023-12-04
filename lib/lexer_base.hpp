#pragma once

#include <concepts>
#include <functional>
#include <iterator>
#include <optional>

namespace pfw {

template <std::bidirectional_iterator I>
struct LexerBase {
    LexerBase(I begin, I end) : iter(std::move(begin)), end(std::move(end)) {
    }

    LexerBase(LexerBase const&) = delete;
    LexerBase& operator=(LexerBase const&) = delete;

protected:
    I iter;
    I end;

    using ValueType = typename std::iterator_traits<I>::value_type;

    template <std::predicate<ValueType> P>
    void Skip(P&& p) {
        while (Expect(std::forward<P>(p))) {
            Consume();
        }
    }

    ValueType Expect(ValueType c) {
        return c == Peek();
    }

    template <std::predicate<ValueType> P>
    bool Expect(P&& p) {
        return std::invoke(std::forward<P>(p), Peek());
    }

    ValueType Peek() {
        if (iter == end) {
            return 0;
        }
        return *iter;
    }

    ValueType Consume() {
        return *(iter++);
    }

    void Consume(size_t n) {
        std::advance(iter, n);
    }
};

}  // namespace pfw