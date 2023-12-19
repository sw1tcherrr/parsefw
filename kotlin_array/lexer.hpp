#pragma once

#include <concepts>
#include <ctre.hpp>
#include <stdexcept>
#include <string_view>
#include <tl/expected.hpp>

#include "../lib/lexer_base.hpp"
#include "../lib/util.hpp"
#include "../lib/token_base.hpp"
#include "token.hpp"

namespace kotlin_array {

template <std::contiguous_iterator I>
struct Lexer : pfw::LexerBase<I> {
private:
    using Base = pfw::LexerBase<I>;
    using Base::iter, Base::end;

public:
    Lexer(I begin, I end) : Base(std::move(begin), std::move(end)) {
    }

    tl::expected<Token, std::string> NextToken() {
        using pfw::util::operator|;
        using pfw::util::operator|=;

        Base::Skip([](unsigned char c) { return std::isspace(c); });

        auto exact_length = Parse<VAR>()
                        | PFW_LAZY(Parse<LANGLE>)
                        | PFW_LAZY(Parse<RANGLE>)
                        | PFW_LAZY(Parse<COLON>)
                        | PFW_LAZY(Parse<SEMICOLON>)
                        | PFW_LAZY(Parse<pfw::token::END>);

        auto variable_length = Parse<ID>()
                            | PFW_LAZY(Parse<pfw::token::END>);
        
        if (!exact_length && !variable_length) {
            return tl::unexpected(std::format("Can't parse any token on line {} at position {}",
                                              Base::Line(), Base::Position()));
        }

        std::string_view ex_str = "";
        if (exact_length) {
            ex_str = std::visit(pfw::token::GetStringValue, exact_length.value());
        }

        std::string_view var_str = "";
        if (variable_length) {
            var_str = std::visit(pfw::token::GetStringValue, variable_length.value());
        }

        if (ex_str.size() >= var_str.size()) {
            Base::Consume(ex_str.size());
            return exact_length.value();
        } else {
            Base::Consume(var_str.size());
            return variable_length.value();
        }
    }

private:

    template <std::derived_from<pfw::token::TokenBase> TokenType>
    std::optional<Token> Parse() {
        auto match = ctre::starts_with<TokenType::kPattern>(iter, end);
        if (match) {
            TokenType res(std::string_view(iter, iter + match.size()), Base::Line(), Base::Position());
            //Base::Consume(match.size());
            return {Token{std::move(res)}};
        }
        return std::nullopt;
    }

    template <>
    std::optional<Token> Parse<pfw::token::END>() {
        if (iter == end) {
            return {pfw::token::END("", Base::Line(), Base::Position())};
        }
        return std::nullopt;
    }
};

} // namespace kotlin_array