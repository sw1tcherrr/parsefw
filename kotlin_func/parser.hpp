#pragma once

#include "../lib/parser_base.hpp"
#include "AST.hpp"
#include "token.hpp"
#include "lexer.hpp"

namespace language::kotlin_func {

template <std::bidirectional_iterator I>
struct Parser : pfw::ParserBase<I, Lexer<I>, Token> {
    Parser(I begin, I end) : Base(std::move(begin), std::move(end)) {}

    using Node = ast::Node;
    std::optional<Node> Parse() {
        NextToken();
        return Declaration();
    }

private:
    using Base = pfw::ParserBase<I, Lexer<I>, Token>;
    using Base::NextToken, Base::Expect;
    using NtNode = pfw::ast::NonterminalNode<Node>;
    using TNode = pfw::ast::TokenNode<Token>;

    void AddTokenChild(NtNode& n) {
        n.AddChild(Node{TNode{this->cur_token}});
    }

    std::optional<Node> Declaration() {
        NtNode res{"Declaration"};
        PFW_TRY(this->template Expect<FUN>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(this->template Expect<ID>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(this->template Expect<LPAREN>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.AddChild(Args()))
        PFW_TRY(this->template Expect<RPAREN>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.AddChild(MaybeReturnType()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Args() {
        if (this->template Expect<ID>()) {
            NtNode res{"Args"};
            std::cout << "Args -> Arg MaybeArgs\n";
            PFW_TRY(res.AddChild(Arg()))
            PFW_TRY(res.AddChild(MaybeArgs()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<RPAREN>()) {
            std::cout << "Args -> eps\n";
            return {Node(NtNode{"Args"})};
        }
        return std::nullopt;
    }

    std::optional<Node> Arg() {
        NtNode res{"Arg"};
        PFW_TRY(this->template Expect<ID>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(this->template Expect<COLON>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.AddChild(Type()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Type() {
        NtNode res{"Type"};
        PFW_TRY(this->template Expect<ID>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.AddChild(MaybeGeneric()))
        return {Node(std::move(res))};
    }

    std::optional<Node> MaybeGeneric() {
        if (this->template Expect<LANGLE>()) {
            NtNode res{"MaybeGeneric"};
            std::cout << "MaybeGeneric -> < Type >\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.AddChild(Type()))
            PFW_TRY(this->template Expect<RANGLE>())
            AddTokenChild(res);
            NextToken();
            return {Node(std::move(res))};
        }
        if (this->template Expect<pfw::Eof>() || this->template Expect<RANGLE>() || this->template Expect<COMMA>() || this->template Expect<RPAREN>()) {
            std::cout << "MaybeGeneric -> eps\n";
            return {Node(NtNode{"MaybeGeneric"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeArgs() {
        if (this->template Expect<COMMA>()) {
            NtNode res{"MaybeArgs"};
            std::cout << "MaybeArgs -> , Args\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.AddChild(Args()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<RPAREN>()) {
            std::cout << "MaybeArgs -> eps\n";
            return {Node(NtNode{"MaybeArgs"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeReturnType() {
        if (this->template Expect<COLON>()) {
            NtNode res{"MaybeReturnType"};
            std::cout << "MaybeReturnType -> : Type\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.AddChild(Type()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<pfw::Eof>()) {
            std::cout << "MaybeReturnType -> eps\n";
            return {Node(NtNode{"MaybeReturnType"})};
        }
        return std::nullopt;
    }
};
} // namespace language::kotlin_func