#pragma once

#include <vector>
#include <ostream>
#include "token.hpp"

namespace parsefw::AST {
using namespace tokens;

struct token_node {
    [[nodiscard]]
    bool is_terminal() const {
        return true;
    }

    [[nodiscard]]
    std::string label() const {
        return std::visit(util::overloaded {
                [](eof) -> std::string { return "EOF"; },
                [](simple s) -> std::string { return {(char)s}; },
                [](keyword const& k) { return "keyword\\n" + k.name; },
                [](id const& i) { return "identifier\\n" + i.name; }
            }, tok);
    }

    template<class T>
    std::vector<T> const& children() const {
        return {};
    }

//private:
    tokens::token tok;
};

template <typename LangNode>
struct nonterminal_node {
    friend LangNode;

    nonterminal_node() = delete;
    nonterminal_node(nonterminal_node const&) = delete;
    nonterminal_node& operator=(nonterminal_node const&) = delete;

    explicit nonterminal_node(std::string name) : name(std::move(name)) {}
    nonterminal_node(nonterminal_node&&) noexcept = default;
    nonterminal_node& operator=(nonterminal_node&&) noexcept = default;

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

//    std::vector<LangNode> const& children() const {
//        return children;
//    }

//private:
    std::string name;
    std::vector<LangNode> children{};
};
}