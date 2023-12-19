#pragma once

#include "../lib/parser_base.hpp"
#include "../lib/util.hpp"
#include "../lib/token_base.hpp"
#include "AST.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <concepts>
#include <format>
#include <tl/expected.hpp>

namespace kotlin_array {

template <std::contiguous_iterator I>
struct Parser : pfw::ParserBase<I, Lexer<I>, Token> {
private:
    using Base = pfw::ParserBase<I, Lexer<I>, Token>;
    using Result = tl::expected<Node, std::string>;
    using Base::NextToken, Base::cur_token;

public:
    Parser(I begin, I end) : Base(std::move(begin), std::move(end)) {
    }

    Result Parse() {
        NextToken();
        return Program();
    }

private:

    void AddTokenChild(NtNode& n) {
        n.AddChild(Node{TNode{cur_token.value()}});
    }

    Result Program() {
        NtNode program("Program");
        
        PFW_TRY(program.TryAddChild(Declaration()));

        PFW_TRY(this->template Expect<pfw::token::END>());

        return program;
    }

    Result Declaration() {
        NtNode decl("Declaration");

        PFW_TRY(this->template Expect<VAR>());
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(this->template Expect<ID>());
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(this->template Expect<COLON>());
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(this->template Expect<ID>());
        if (std::visit(pfw::token::GetStringValue, cur_token.value()) != "Array") {
            return tl::unexpected(std::format("Expected Array type, got {}", cur_token.value()));
        }
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(this->template Expect<LANGLE>());
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(decl.TryAddChild(Type()))

        PFW_TRY(this->template Expect<RANGLE>());
        AddTokenChild(decl);
        NextToken();

        PFW_TRY(this->template Expect<SEMICOLON>());
        AddTokenChild(decl);
        NextToken();

        return decl;
    }

    Result Type() {
        NtNode type("Type");

        PFW_TRY(this->template Expect<ID>());
        AddTokenChild(type);
        NextToken();

        return type;
    }

};

} // namespace kotlin_array