#pragma once

#include <ostream>
#include <fstream>

namespace parsefw::graphviz {

template <typename LangNode>
struct graphviz_node {
    void set_id(int id_) const {
        id = id_;
    }

    void print_attributes(std::ostream& os) const {
        os << id << "[";
        os << "label=\"" << self().label() << "\"";
        if (self().is_terminal()) {
            os << " color=red";
        }
        os << "]\n";
    }

    void print_children(std::ostream& os) const {
        if (self().is_terminal()) return;

        os << id << " -> {";
        for (auto const& c : self().children()) {
            os << as_gf_node(c).id << " ";
        }
        os << "}\n";
    }

    static graphviz_node const& as_gf_node(LangNode const& ln) {
        return static_cast<graphviz_node const&>(ln);
    }

private:
    mutable int id{-1};

    LangNode const& self() const {
        return static_cast<LangNode const&>(*this);
    }
};

namespace {
template<typename LangNode>
int AST_to_DOT_visit(std::ostream &os, LangNode const &node, int cnt = 0) {
    auto const &gf_root = graphviz_node<LangNode>::as_gf_node(node);
    gf_root.set_id(cnt);
    gf_root.print_attributes(os);
    if (!node.is_terminal()) {
        for (auto const &c: node.children()) {
            cnt = AST_to_DOT_visit(os, c, ++cnt);
        }
        gf_root.print_children(os);
    }
    return cnt;
}
}

template <typename LangNode>
void AST_to_DOT(std::ostream& os, LangNode const& root) {
    os << "digraph {\n";
    AST_to_DOT_visit(os, root, 0);
    os << "}\n";
}

}