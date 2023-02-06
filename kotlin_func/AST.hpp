#pragma once
#include <variant>
#include <concepts>
#include <cassert>
#include "../lib/AST.hpp"
#include "../lib/graphviz.hpp"

namespace language::kotlin_func::AST {
struct lang_node : parsefw::graphviz::graphviz_node<lang_node> {
    template <typename Node>
    explicit lang_node(Node n) : value(std::move(n)) {}

    [[nodiscard]]
    bool is_terminal() const {
        return std::visit([](auto&& v) {return v.is_terminal(); }, value);
    }

    [[nodiscard]]
    std::string label() const {
        if (auto t = std::get_if<token_node>(&value)) {
            return t->label();
        } else if (auto nt = std::get_if<nt_node>(&value)) {
            return nt->label();
        }
        return "aboba";
//        return std::visit([](auto&& v) {
//            return v.label();
//            }, value);
    }

    [[nodiscard]]
    std::vector<lang_node> const& children() const {
        auto nt = as_nt_node();
        assert(nt);
        return nt->children;
    }

private:
    using token_node = parsefw::AST::token_node;
    using nt_node = parsefw::AST::nonterminal_node<lang_node>;
    std::variant<token_node, nt_node> value;

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
};

}