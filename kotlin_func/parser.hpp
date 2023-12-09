#pragma once

#include "../lib/parser_base.hpp"
#include "../lib/util.hpp"
#include "AST.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <format>
#include <tl/expected.hpp>

namespace language::kotlin_func {

using namespace ast;

template <std::bidirectional_iterator I>
struct Parser : pfw::ParserBase<I, Lexer<I>, Token> {
    Parser(I begin, I end) : Base(std::move(begin), std::move(end)) {
    }

    using Result = tl::expected<Node, std::string>;
    
    Result Parse() {
        NextToken();
        return Declaration();
    }

private:
    using Base = pfw::ParserBase<I, Lexer<I>, Token>;
    using Base::NextToken;

    void AddTokenChild(NtNode& n) {
        n.AddChild(Node{TNode{this->cur_token}});
    }

    Result Declaration() {
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
        PFW_TRY(res.TryAddChild(Args()))
        PFW_TRY(this->template Expect<RPAREN>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.TryAddChild(MaybeReturnType()))
        return {Node(std::move(res))};
    }

    Result Args() {
        if (this->template Expect<ID>()) {
            NtNode res{"Args"};
            std::cout << "Args -> Arg MaybeArgs\n";
            PFW_TRY(res.TryAddChild(Arg()))
            PFW_TRY(res.TryAddChild(MaybeArgs()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<RPAREN>()) {
            std::cout << "Args -> eps\n";
            return {Node(NtNode{"Args"})};
        }

        return tl::unexpected(std::format("Expected ID or RPAREN, got {}\n", this->cur_token));
    }

    Result Arg() {
        NtNode res{"Arg"};
        PFW_TRY(this->template Expect<ID>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(this->template Expect<COLON>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.TryAddChild(Type()))
        return {Node(std::move(res))};
    }

    Result Type() {
        NtNode res{"Type"};
        PFW_TRY(this->template Expect<ID>())
        AddTokenChild(res);
        NextToken();
        PFW_TRY(res.TryAddChild(MaybeGeneric()))
        return {Node(std::move(res))};
    }

    Result MaybeGeneric() {
        if (this->template Expect<LANGLE>()) {
            NtNode res{"MaybeGeneric"};
            std::cout << "MaybeGeneric -> < Type >\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.TryAddChild(Type()))
            PFW_TRY(this->template Expect<RANGLE>())
            AddTokenChild(res);
            NextToken();
            return {Node(std::move(res))};
        }
        if (this->template Expect<pfw::token::END>() || this->template Expect<RANGLE>()
            || this->template Expect<COMMA>() || this->template Expect<RPAREN>()) {
            std::cout << "MaybeGeneric -> eps\n";
            return {Node(NtNode{"MaybeGeneric"})};
        }
        return tl::unexpected(std::format("Expected LANGLE or RANGLE or COMMA or RPAREN or END, got {}\n", this->cur_token));
    }

    Result MaybeArgs() {
        if (this->template Expect<COMMA>()) {
            NtNode res{"MaybeArgs"};
            std::cout << "MaybeArgs -> , Args\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.TryAddChild(Args()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<RPAREN>()) {
            std::cout << "MaybeArgs -> eps\n";
            return {Node(NtNode{"MaybeArgs"})};
        }
        return tl::unexpected(std::format("Expected COMMA or RPAREN, got {}\n", this->cur_token));
    }

    Result MaybeReturnType() {
        if (this->template Expect<COLON>()) {
            NtNode res{"MaybeReturnType"};
            std::cout << "MaybeReturnType -> : Type\n";
            AddTokenChild(res);
            NextToken();
            PFW_TRY(res.TryAddChild(Type()))
            return {Node(std::move(res))};
        }
        if (this->template Expect<pfw::token::END>()) {
            std::cout << "MaybeReturnType -> eps\n";
            return {Node(NtNode{"MaybeReturnType"})};
        }
        return tl::unexpected(std::format("Expected COLON or END, got {}\n", this->cur_token));
    }
};
}  // namespace language::kotlin_func