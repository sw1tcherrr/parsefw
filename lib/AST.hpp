#pragma once

#include <optional>
#include <ostream>
#include <span>
#include <tl/expected.hpp>
#include <variant>
#include <vector>

#include "token_base.hpp"
#include "util.hpp"

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
        return std::string(std::visit(pfw::token::GetStringValue, m_tok));
    }

    [[nodiscard]]
    std::span<const LangNode> Children() const {
        return {};
    }

    [[nodiscard]]
    std::span<LangNode> Children() {
        return {};
    }

    bool operator==(TokenNode const& other) const {
        return m_tok == other.m_tok;
    }

private:
    Token m_tok;
};

template <typename LangNode>
struct NonterminalNode {
    NonterminalNode() = delete;
    explicit NonterminalNode(std::string name) : m_name(std::move(name)) {
    }

    NonterminalNode(std::string name, std::vector<LangNode>&& children) 
    : m_name(std::move(name)), m_children(std::move(children)) {
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

    tl::expected<std::monostate, std::string> TryAddChild(tl::expected<LangNode, std::string>&& maybe_child) {
        if (!maybe_child) {
            return tl::unexpected(maybe_child.error());
        }
        m_children.push_back(std::move(*maybe_child));
        return {};
    }

    NonterminalNode& AddChild(LangNode&& child) {
        m_children.push_back(std::move(child));
        return *this;
    }

    bool operator==(NonterminalNode const& other) const {
        return m_children == other.m_children;
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
    LangNodeBase(Node n) : value(std::move(n)) { // NOLINT (should be implicit)
    }

    template <typename... Visitors>
    auto Visit(Visitors&&... vs) {
        return std::visit(util::overloaded(vs...), value);
    }

    template <typename... Visitors>
    auto Visit(Visitors&&... vs) const {
        return std::visit(util::overloaded(vs...), value);
    }

    [[nodiscard]]
    bool IsTerminal() const {
        return Visit([](auto const& v) { return v.IsTerminal(); });
    }

    [[nodiscard]]
    std::string Label() const {
        return Visit([](auto const& v) { return v.Label(); });
    }

    [[nodiscard]]
    std::span<const LangNode> Children() const& {
        return Visit([](auto const& v) { return v.Children(); });
    }

    [[nodiscard]]
    std::span<LangNode> Children() & {
        return Visit([](auto& v) { return v.Children(); });
    }

    bool operator==(LangNodeBase const& other) const {
        return value == other.value;
    }

protected:
    std::variant<Nodes...> value;
};

}  // namespace pfw::ast