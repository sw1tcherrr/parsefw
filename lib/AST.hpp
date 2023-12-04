#pragma once

#include <optional>
#include <ostream>
#include <span>
#include <variant>
#include <vector>

#include "token_base.hpp"

namespace pfw::ast {

template <typename Token, typename LangNode>
struct TokenNode {
    explicit TokenNode(Token tok) : m_tok(std::move(tok)) {
    }

    [[nodiscard]]
    bool IsTerminal() const {
        return true;
    }

    [[nodiscard]]
    std::string Label() const {
        return std::string(std::visit([](auto const& t) { return pfw::token::GetStringValue(t); }, m_tok));
    }

    [[nodiscard]]
    std::span<const LangNode> Children() const {
        return {};
    }

    [[nodiscard]]
    std::span<LangNode> Children() {
        return {};
    }

private:
    Token m_tok;
};

template <typename LangNode>
struct NonterminalNode {
    NonterminalNode() = delete;
    explicit NonterminalNode(std::string name) : m_name(std::move(name)) {
    }

    [[nodiscard]]
    bool IsTerminal() const {
        return false;
    }

    [[nodiscard]]
    std::string Label() const {
        return m_name;
    }

    [[nodiscard]]
    std::span<const LangNode> Children() const& {
        return m_children;
    }

    [[nodiscard]]
    std::span<LangNode> Children() & {
        return m_children;
    }

    bool AddChild(std::optional<LangNode>&& maybe_child) {
        if (!maybe_child) {
            return false;
        }
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
    explicit LangNodeBase(Node n) : value(std::move(n)) {
    }

    [[nodiscard]]
    bool IsTerminal() const {
        return std::visit([](auto& v) { return v.IsTerminal(); }, value);
    }

    [[nodiscard]]
    std::string Label() const {
        return std::visit([](auto& v) { return v.Label(); }, value);
    }

    [[nodiscard]]
    std::span<const LangNode> Children() const& {
        return std::visit([](auto& v) { return v.Children(); }, value);
    }

    [[nodiscard]]
    std::span<LangNode> Children() & {
        return std::visit([](auto& v) { return v.Children(); }, value);
    }

protected:
    std::variant<Nodes...> value;
};

}  // namespace pfw::ast