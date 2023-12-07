#pragma once

#include <concepts>
#include <functional>
#include <iterator>
#include <optional>

namespace pfw {

template <std::contiguous_iterator I> 
    requires std::same_as<std::remove_cv_t<std::iter_value_t<I>>, char>
struct LexerBase {
    LexerBase(I begin, I end) : iter(std::move(begin)), end(std::move(end)) {
        lines.push_back(iter);
    }

    LexerBase(LexerBase const&) = delete;
    LexerBase& operator=(LexerBase const&) = delete;

protected:
    I iter;
    I end;
    std::vector<I> lines;

    using ValueType = typename std::iter_value_t<I>;

    template <std::predicate<ValueType> P>
    void Skip(P&& p) {
        while (Expect(std::forward<P>(p))) {
            if (Expect('\n')) {
                lines.push_back(iter);
            }
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