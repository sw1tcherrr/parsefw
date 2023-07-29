#pragma once

#include "../lib/parser_base.hpp"
#include "AST.hpp"
#include "token.hpp"
#include "lexer.hpp"

namespace language::kotlin_func {

template <std::bidirectional_iterator I>
struct parser : parsefw::parser_base<I, lexer<I>, token> {
    parser(I begin, I end) : base(std::move(begin), std::move(end)) {}

    using Node = AST::node;
    std::optional<Node> parse() {
        next_token();
        return Declaration();
    }

private:
    using base = parsefw::parser_base<I, lexer<I>, token>;
    using base::next_token, base::expect;
    using nt_node = parsefw::AST::nonterminal_node<Node>;
    using t_node = parsefw::AST::token_node<token>;

    void add_token_child(nt_node& n) {
        n.add_child(Node{t_node{this->cur_token}});
    }

    std::optional<Node> Declaration() {
        nt_node res{"Declaration"};
        PFW_TRY(this->template expect<FUN>())
        add_token_child(res);
        next_token();
        PFW_TRY(this->template expect<ID>())
        add_token_child(res);
        next_token();
        PFW_TRY(this->template expect<LPAREN>())
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(Args()))
        PFW_TRY(this->template expect<RPAREN>())
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(MaybeReturnType()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Args() {
        if (this->template expect<ID>()) {
            nt_node res{"Args"};
            std::cout << "Args -> Arg MaybeArgs\n";
            PFW_TRY(res.add_child(Arg()))
            PFW_TRY(res.add_child(MaybeArgs()))
            return {Node(std::move(res))};
        }
        if (this->template expect<RPAREN>()) {
            std::cout << "Args -> eps\n";
            return {Node(nt_node{"Args"})};
        }
        return std::nullopt;
    }

    std::optional<Node> Arg() {
        nt_node res{"Arg"};
        PFW_TRY(this->template expect<ID>())
        add_token_child(res);
        next_token();
        PFW_TRY(this->template expect<COLON>())
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(Type()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Type() {
        nt_node res{"Type"};
        PFW_TRY(this->template expect<ID>())
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(MaybeGeneric()))
        return {Node(std::move(res))};
    }

    std::optional<Node> MaybeGeneric() {
        if (this->template expect<LANGLE>()) {
            nt_node res{"MaybeGeneric"};
            std::cout << "MaybeGeneric -> < Type >\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Type()))
            PFW_TRY(this->template expect<RANGLE>())
            add_token_child(res);
            next_token();
            return {Node(std::move(res))};
        }
        if (this->template expect<parsefw::eof>() || this->template expect<RANGLE>() || this->template expect<COMMA>() || this->template expect<RPAREN>()) {
            std::cout << "MaybeGeneric -> eps\n";
            return {Node(nt_node{"MaybeGeneric"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeArgs() {
        if (this->template expect<COMMA>()) {
            nt_node res{"MaybeArgs"};
            std::cout << "MaybeArgs -> , Args\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Args()))
            return {Node(std::move(res))};
        }
        if (this->template expect<RPAREN>()) {
            std::cout << "MaybeArgs -> eps\n";
            return {Node(nt_node{"MaybeArgs"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeReturnType() {
        if (this->template expect<COLON>()) {
            nt_node res{"MaybeReturnType"};
            std::cout << "MaybeReturnType -> : Type\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Type()))
            return {Node(std::move(res))};
        }
        if (this->template expect<parsefw::eof>()) {
            std::cout << "MaybeReturnType -> eps\n";
            return {Node(nt_node{"MaybeReturnType"})};
        }
        return std::nullopt;
    }
};
} // namespace language::kotlin_func