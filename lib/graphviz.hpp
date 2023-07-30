#pragma once

#include <ostream>
#include <fstream>

namespace pfw::graphviz {

template <typename LangNode>
struct GraphvizNode {
    void SetId(int id) const {
        m_id = id;
    }

    void PrintAttributes(std::ostream& os) const {
        os << m_id << "[";
        os << "label=\"" << Self().Label() << "\"";
        if (Self().IsTerminal()) {
            os << " color=red";
        }
        os << "]\n";
    }

    void PrintChildren(std::ostream& os) const {
        if (Self().IsTerminal()) { return;
}

        os << m_id << " -> {";
        for (auto const& c : Self().Children()) {
            os << AsGfNode(c).m_id << " ";
        }
        os << "}\n";
    }

    static GraphvizNode const& AsGfNode(LangNode const& ln) {
        return static_cast<GraphvizNode const&>(ln);
    }

private:
    mutable int m_id{-1};

    LangNode const& Self() const {
        return static_cast<LangNode const&>(*this);
    }
};

namespace {
template<typename LangNode>
int AstToDotVisit(std::ostream &os, LangNode const &node, int cnt = 0) {
    auto const &gf_root = GraphvizNode<LangNode>::AsGfNode(node);
    gf_root.SetId(cnt);
    gf_root.PrintAttributes(os);
    if (!node.IsTerminal()) {
        for (auto const &c: node.Children()) {
            cnt = AstToDotVisit(os, c, ++cnt);
        }
        gf_root.PrintChildren(os);
    }
    return cnt;
}
}

template <typename LangNode>
void AstToDot(std::ostream& os, LangNode const& root) {
    os << "digraph {\n";
    AstToDotVisit(os, root, 0);
    os << "}\n";
}

}