#pragma once

#include <vector>
#include <ostream>
#include "token_base.hpp"

namespace parsefw::AST {

template <typename Token>
struct token_node {
    explicit token_node(Token tok) : tok(std::move(tok)) {}

    [[nodiscard]]
    bool is_terminal() const {
        return true;
    }

    [[nodiscard]]
    std::string label() const {
        return /*std::visit(util::overloaded {
                [](eof) -> std::string { return "EOF"; },
                [](simple s) -> std::string { return {(char)s}; },
                [](keyword const& k) { return "keyword\\n" + k.name; },
                [](id const& i) { return "identifier\\n" + i.name; }
            }, tok);*/
        "aboba";
    }

    template<class T>
    std::vector<T> const& children() const {
        return {};
    }

private:
    Token tok;
};

template <typename LangNode>
struct nonterminal_node {
    nonterminal_node() = delete;
    explicit nonterminal_node(std::string name) : name(std::move(name)) {}

    [[nodiscard]]
    bool is_terminal() const {
        return false;
    }

    [[nodiscard]]
    std::string label() const noexcept {
        return name;
    }

    bool add_child(std::optional<LangNode>&& maybe_child) {
        if (!maybe_child) { return false; }
        children.push_back(std::move(*maybe_child));
        return true;
    }

    bool add_child(LangNode&& child) {
        children.push_back(std::move(child));
        return true;
    }

private:
    template <typename LNode, typename... Nodes>
    friend struct lang_node_base;

    std::string name;
    std::vector<LangNode> children{};
};

template <typename LangNode, typename... Nodes>
struct lang_node_base {
    template <typename Node>
    explicit lang_node_base(Node n) : value(std::move(n)) {}

    [[nodiscard]]
    bool is_terminal() const {
        return std::visit([](auto&& v) {return v.is_terminal(); }, value);
    }

    [[nodiscard]]
    std::string label() const {
        return std::visit([](auto &&v) {
            return v.label();
        }, value);
    }

    // Pre: this LangNode is non-terminal node
    [[nodiscard]]
    std::vector<LangNode> const& children() const {
        auto* nt = as_nt_node();
        assert(nt);
        return nt->children;
    }

protected:
    using nt_node = nonterminal_node<LangNode>;
    [[nodiscard]]
    nt_node const* as_nt_node() const {
        return std::visit([]<typename T>(T const& v) -> nt_node const*{
            if constexpr (std::is_base_of_v<nt_node, T>) {
                return &v;
            } else {
                return nullptr;
            }
        }, value);
    }

    std::variant<Nodes...> value;
};

}