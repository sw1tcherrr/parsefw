#pragma once

#include <vector>
#include <ostream>
#include "token_base.hpp"

namespace pfw::ast {

template <typename Token>
struct TokenNode {
    explicit TokenNode(Token tok) : m_tok(std::move(tok)) {}

    [[nodiscard]]
    bool IsTerminal() const {
        return true;
    }

    [[nodiscard]]
    std::string Label() const {
        return /*std::visit(util::overloaded {
                [](eof) -> std::string { return "EOF"; },
                [](simple s) -> std::string { return {(char)s}; },
                [](keyword const& k) { return "keyword\\n" + k.name; },
                [](id const& i) { return "identifier\\n" + i.name; }
            }, tok);*/
        "aboba";
    }

    template<class T>
    std::vector<T> const& Children() const {
        return {};
    }

private:
    Token m_tok;
};

template <typename LangNode>
struct NonterminalNode {
    NonterminalNode() = delete;
    explicit NonterminalNode(std::string name) : m_name(std::move(name)) {}

    [[nodiscard]]
    bool IsTerminal() const {
        return false;
    }

    [[nodiscard]]
    std::string Label() const noexcept {
        return m_name;
    }

    bool AddChild(std::optional<LangNode>&& maybe_child) {
        if (!maybe_child) { return false; }
        m_children.push_back(std::move(*maybe_child));
        return true;
    }

    bool AddChild(LangNode&& child) {
        m_children.push_back(std::move(child));
        return true;
    }

private:
    template <typename LNode, typename... Nodes>
    friend struct LangNodeBase;

    std::string m_name;
    std::vector<LangNode> m_children{};
};

template <typename LangNode, typename... Nodes>
struct LangNodeBase {
    template <typename Node>
    explicit LangNodeBase(Node n) : value(std::move(n)) {}

    [[nodiscard]]
    bool IsTerminal() const {
        return std::visit([](auto&& v) {return v.IsTerminal(); }, value);
    }

    [[nodiscard]]
    std::string Label() const {
        return std::visit([](auto &&v) {
            return v.Label();
        }, value);
    }

    // Pre: this LangNode is non-terminal node
    [[nodiscard]]
    std::vector<LangNode> const& Children() const {
        auto* nt = AsNtNode();
        assert(nt);
        return nt->m_children;
    }

protected:
    using NtNode = NonterminalNode<LangNode>;
    [[nodiscard]]
    NtNode const* AsNtNode() const {
        return std::visit([]<typename T>(T const& v) -> NtNode const*{
            if constexpr (std::is_base_of_v<NtNode, T>) {
                return &v;
            } else {
                return nullptr;
            }
        }, value);
    }

    std::variant<Nodes...> value;
};

}