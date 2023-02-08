#include "../lib/parser_base.hpp"
#include "AST.hpp"

namespace language::kotlin_func {

using namespace parsefw::tokens;

template <std::input_iterator I>
struct parser : parsefw::parser_base<I> {
    parser(I begin, I end) : base(std::move(begin), std::move(end)) {}

    using Node = AST::node;
    std::optional<Node> parse() {
        next_token();
        return Declaration();
    }

private:
    using base = parsefw::parser_base<I>;
    using base::next_token, base::expect_eof, base::expect_simple, base::expect_id, base::expect_keyword;
    using nt_node = parsefw::AST::nonterminal_node<Node>;
    using t_node = parsefw::AST::token_node;

    void add_token_child(nt_node& n) {
        n.add_child(Node{t_node{this->cur_token}});
    }

    std::optional<Node> Declaration() {
        nt_node res{"Declaration"};
        PFW_TRY(expect_keyword("fun"))
        add_token_child(res);
        next_token();
        PFW_TRY(expect_id())
        add_token_child(res);
        next_token();
        PFW_TRY(expect_simple(LPAREN))
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(Args()))
        PFW_TRY(expect_simple(RPAREN))
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(MaybeReturnType()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Args() {
        if (expect_id()) {
            nt_node res{"Args"};
            std::cout << "Args -> Arg MaybeArgs\n";
            PFW_TRY(res.add_child(Arg()))
            PFW_TRY(res.add_child(MaybeArgs()))
            return {Node(std::move(res))};
        }
        if (expect_simple(RPAREN)) {
            std::cout << "Args -> eps\n";
            return {Node(nt_node{"Args"})};
        }
        return std::nullopt;
    }

    std::optional<Node> Arg() {
        nt_node res{"Arg"};
        PFW_TRY(expect_id())
        add_token_child(res);
        next_token();
        PFW_TRY(expect_simple(COLON))
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(Type()))
        return {Node(std::move(res))};
    }

    std::optional<Node> Type() {
        nt_node res{"Type"};
        PFW_TRY(expect_id())
        add_token_child(res);
        next_token();
        PFW_TRY(res.add_child(MaybeGeneric()))
        return {Node(std::move(res))};
    }

    std::optional<Node> MaybeGeneric() {
        if (expect_simple(LANGLE)) {
            nt_node res{"MaybeGeneric"};
            std::cout << "MaybeGeneric -> < Type >\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Type()))
            PFW_TRY(expect_simple(RANGLE))
            add_token_child(res);
            next_token();
            return {Node(std::move(res))};
        }
        if (expect_eof() || expect_simple(RANGLE) || expect_simple(COMMA) || expect_simple(RPAREN)) {
            std::cout << "MaybeGeneric -> eps\n";
            return {Node(nt_node{"MaybeGeneric"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeArgs() {
        if (expect_simple(COMMA)) {
            nt_node res{"MaybeArgs"};
            std::cout << "MaybeArgs -> , Args\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Args()))
            return {Node(std::move(res))};
        }
        if (expect_simple(RPAREN)) {
            std::cout << "MaybeArgs -> eps\n";
            return {Node(nt_node{"MaybeArgs"})};
        }
        return std::nullopt;
    }

    std::optional<Node> MaybeReturnType() {
        if (expect_simple(COLON)) {
            nt_node res{"MaybeReturnType"};
            std::cout << "MaybeReturnType -> : Type\n";
            add_token_child(res);
            next_token();
            PFW_TRY(res.add_child(Type()))
            return {Node(std::move(res))};
        }
        if (expect_eof()) {
            std::cout << "MaybeReturnType -> eps\n";
            return {Node(nt_node{"MaybeReturnType"})};
        }
        return std::nullopt;
    }
};
} // namespace language::kotlin_func