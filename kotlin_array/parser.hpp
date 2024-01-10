#pragma once

#include <pfw/parser_base.hpp>
#include <pfw/util.hpp>
#include <pfw/token_base.hpp>
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

        PFW_TRY(decl.TryAddChild(VariableList()));

        PFW_TRY(this->template Expect<SEMICOLON>());
        AddTokenChild(decl);
        NextToken();

        return decl;
    }

    Result VariableList() {
        NtNode list("VariableList");

        PFW_TRY(list.TryAddChild(Variable()));

        PFW_TRY(list.TryAddChild(MaybeListTail()));

        return list;
    }

    Result MaybeListTail() {
        NtNode tail("MaybeListTail");

        if (this->template Expect<COMMA>()) {
            AddTokenChild(tail);
            NextToken();

            PFW_TRY(tail.TryAddChild(VariableList()));
        } else {
            // MaybeListTail -> eps
            PFW_TRY(this->template Expect<SEMICOLON>());
            // check, but dont consume 
        }
        return tail;
    }

    Result Variable() {
        NtNode var("Variable");

        PFW_TRY(this->template Expect<ID>());
        AddTokenChild(var);
        NextToken();

        PFW_TRY(this->template Expect<COLON>());
        AddTokenChild(var);
        NextToken();

        PFW_TRY(this->template Expect<ID>());
        if (std::visit(pfw::token::GetStringValue, cur_token.value()) != "Array") {
            return tl::unexpected(std::format("Expected Array type, got {}", cur_token.value()));
        }
        AddTokenChild(var);
        NextToken();

        PFW_TRY(this->template Expect<LANGLE>());
        AddTokenChild(var);
        NextToken();

        PFW_TRY(var.TryAddChild(Type()))

        PFW_TRY(this->template Expect<RANGLE>());
        AddTokenChild(var);
        NextToken();

        return var;
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