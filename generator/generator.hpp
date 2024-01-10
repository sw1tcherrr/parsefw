#pragma once

#include <concepts>
#include <format>
#include <fstream>
#include <string>
#include "grammar.hpp"
#include "rule.hpp"

struct Coder {
    std::ofstream out;
    int indent;

    void Line(std::string_view line) {
        WriteIndented(line);
        out << "\n";
    }

    void Line() {
        Line("");
    }

    void WriteIndented(std::string_view str) {
        for (int i = 0; i < indent; ++i) {
            out << "\t";
        }
        out << str;
    }

    template <std::invocable F>
    void Scope(std::string&& prefix, F&& content) {
        ScopeImpl(prefix + " {", "}", true, std::forward<F>(content));
    }

    template <std::invocable F>
    void Scope(F&& content) {
        ScopeImpl("{", "}", true, std::forward<F>(content));
    }

    template <std::invocable F>
    void Struct(std::string&& prefix, F&& content) {
        ScopeImpl(prefix + " {", "};", true, std::forward<F>(content));
    }

    template <std::invocable F>
    void Namespace(std::string const& ns, F&& content) {
        ScopeImpl("namespace " + ns + " {\n", "\n} // namespace " + ns, false, std::forward<F>(content));
    }

private:
    template <std::invocable F>
    void ScopeImpl(std::string_view start, std::string_view end, bool needs_indent, F&& content) {
        Line(start);
        if (needs_indent) { ++indent; }
        std::invoke(std::forward<F>(content));
        if (needs_indent) { --indent; }
        Line(end);
    }
};

struct Generator {
    Grammar g;
    std::unordered_map<std::string, std::string> tokens;
    std::string skip;
    std::string ns;

    #define fmt std::format

    void GenerateToken() {
        Coder c(std::ofstream("token.hpp"));

        c.Line("#pragma once");
        c.Line();
        c.Line("#include <pfw/token_base.hpp>"); // TODO
        c.Line();
        c.Namespace(ns, [&]() {
        std::string name_list;
        for (auto it = tokens.cbegin(), end = tokens.cend(); it != end; ++it) {
            auto const& [name, regex] = *it;
            c.Line("PFW_TOKEN(" + name + ", " + "R\"(" + regex + ")\")");
            name_list += name;
            if (std::next(it) != end) {
                name_list += ',';
            }
        }
        c.Line("using END = pfw::token::END;");
        c.Line();
        c.Line("using Token = pfw::token::TokenType<" + name_list + ">;");
        });
    }

    void GenerateLexer() {
        Coder c(std::ofstream("lexer.hpp"));

        c.Line("#pragma once");
        c.Line();
        c.Line("#include <concepts>");
        c.Line("#include <ctre.hpp>");
        c.Line("#include <stdexcept>");
        c.Line("#include <string_view>");
        c.Line("#include <tl/expected.hpp>");
        c.Line();
        c.Line("#include <pfw/lexer_base.hpp>");
        c.Line("#include <pfw/token_base.hpp>");
        c.Line("#include \"token.hpp\"");
        c.Line();

        c.Namespace(ns, [&]() {
        c.Line("template <std::contiguous_iterator I>");
        c.Struct("struct Lexer : pfw::LexerBase<I>", [&]() {
            c.Line("private:");
            c.Line("using Base = pfw::LexerBase<I>;");
            c.Line("using Base::iter, Base::end;");
            c.Line();
            c.Line("public:");
            c.Scope("Lexer(I begin, I end) : Base(std::move(begin), std::move(end))", [](){});
            c.Scope("tl::expected<Token, std::string> NextToken()", [&]() {
                c.Line("Base::Skip(" + skip + ");");
                c.Line();
                c.Line("std::optional<Token> best_token;");
                for (auto const& [name, _] : tokens) {
                    c.Scope([&]() {
                        c.Line("auto res = Parse<" + name + ">();");
                        c.Scope("if (res && (!best_token || std::visit(pfw::token::GetStringValue, res.value()).size() > std::visit(pfw::token::GetStringValue, best_token.value()).size()))", [&]() {
                            c.Line("best_token = res;");
                        });
                    });
                    c.Line();
                }
                c.Scope("if (!best_token)", [&]() {
                    c.Line("best_token = Parse<pfw::token::END>();");
                });
                c.Line();
                c.Scope("if (!best_token)", [&]() {
                    c.Line("return tl::unexpected(std::format(\"Can't parse any token on line {} at position {}\", Base::Line(), Base::Position()));");
                });
                c.Line();
                c.Line("Base::Consume(std::visit(pfw::token::GetStringValue, best_token.value()).size());");
                c.Line("return best_token.value();");
            });
            c.Line();
            c.Line("private:");
            c.Line();
            c.Line("template <std::derived_from<pfw::token::TokenBase> TokenType>");
            c.Scope("std::optional<Token> Parse()", [&]() {
                c.Line("auto match = ctre::starts_with<TokenType::kPattern>(iter, end);");
                c.Scope("if (match)", [&]() {
                    c.Line("TokenType res(std::string_view(iter, iter + match.size()), Base::Line(), Base::Position());");
                    c.Line("return {Token{std::move(res)}};");
                });
                c.Line("return std::nullopt;");
            });
            c.Line();
            c.Line("template<>");
            c.Scope("std::optional<Token> Parse<pfw::token::END>()", [&]() {
                c.Scope("if (iter == end)", [&]() {
                    c.Line("return {pfw::token::END(\"\", Base::Line(), Base::Position())};");
                });
                c.Line("return std::nullopt;");
            });
        });
        });
    }

    void GenerateAST() {
        Coder c(std::ofstream("AST.hpp"));

        c.Line("#pragma once");
        c.Line();
        c.Line("#include <pfw/AST.hpp>");
        c.Line("#include <pfw/graphviz.hpp>");
        c.Line("#include \"token.hpp\"");
        c.Line();

        c.Namespace(ns, [&]() {
        c.Line("struct Node;");
        c.Line();

        for (auto const& [name, rule] : g.rules) {
            c.Line("template <typename LangNode>");
            c.Struct("struct " + name + "NodeT : pfw::ast::NonterminalNode<LangNode>", [&]() {
                c.Scope(name + "NodeT() : pfw::ast::NonterminalNode<LangNode>(\"" + name + "\")", [](){});
                c.Line();
                for (auto const& attr : rule.attrs) {
                    c.Line(attr.type + " " + attr.name + ";");
                }
            });
            c.Line();
        }

        std::string base = "using Base = pfw::ast::LangNodeBase<Node, ";
        for (auto const& [name, _] : g.rules) {
            base += name + "Node, ";
            c.Line("using " + name + "Node" + " = " + name + "NodeT<Node>;");
        }
        c.Line("using _TokenNode = pfw::ast::TokenNode<Token, Node>;");
        c.Line("using _NtNode = pfw::ast::NonterminalNode<Node>;");
        c.Line();

        base += "_TokenNode>;";
        c.Line(base);
        c.Line();
        c.Struct("struct Node : Base, pfw::graphviz::GraphvizNode<Node>", [&]() {
            c.Line("using Base::Base;");
        });
        });
    }

    void GenerateParser() {
        Coder c(std::ofstream("parser.hpp"));

        c.Line("#pragma once");
        c.Line();
        c.Line("#include <tl/expected.hpp>");
        c.Line("#include <format>");
        c.Line();
        c.Line("#include <pfw/parser_base.hpp>");
        c.Line("#include <pfw/util.hpp>");
        c.Line();
        c.Line("#include \"token.hpp\"");
        c.Line("#include \"lexer.hpp\"");
        c.Line("#include \"AST.hpp\"");
        c.Line();

        c.Namespace(ns, [&]() {
        c.Line("template <std::bidirectional_iterator I>");
        c.Struct("struct Parser : pfw::ParserBase<I, Lexer<I>, Token>", [&]() {
            c.Line("private:");
            c.Line("using Base = pfw::ParserBase<I, Lexer<I>, Token>;");
            c.Line("using Base::NextToken, Base::cur_token;");
            c.Line();
            
            c.Line("public:");
            c.Scope("Parser(I begin, I end) : Base(std::move(begin), std::move(end))", [](){});
            c.Line();

            c.Line("template <typename T>");
            c.Line("using Result = tl::expected<T, std::string>;");
            c.Line();

            c.Scope("Result<Node> Parse()", [&]() {
                c.Line("NextToken();");
                c.Line(fmt("auto res = {}();", g.start));
                c.Line("PFW_TRY(res)");
                c.Line("return Node(res.value());");
            });
            c.Line();

            c.Line("private:");
            c.Line();

            for (auto const& [name, rule] : g.rules) {
                c.Scope(fmt("Result<{}Node> {}({})", name, name, MakeArgDecl(rule)), [&]() {
                    c.Line(fmt("{}Node _0;", name));
                    for (auto const& production : rule.variants) {
                        c.Scope(fmt("if ({})", MakeCondition(name, production)), [&]() {
                            for (int idx = 1; auto const& elt : production) {
                                auto var = fmt("_{}", idx);
                                auto res = fmt("res{}", idx);
                                std::visit(pfw::util::overloaded {
                                    [&](Token const& t) {
                                        c.Line(fmt("PFW_TRY(this->template Expect<{}>())", t.name));
                                        c.Line(fmt("auto {} = _TokenNode(cur_token.value());", var));
                                        c.Line(fmt("_0.AddChild({});", var));
                                        c.Line("NextToken();");
                                        c.Line();
                                    },
                                    [&](RuleRef const& r) {
                                        c.Line(fmt("auto {} = {}({});", res, r.name, MakeArgPass(r)));
                                        c.Line(fmt("PFW_TRY({})", res));
                                        c.Line(fmt("auto {} = {}.value();", var, res));
                                        c.Line(fmt("_0.AddChild({});", var));
                                        c.Line();
                                    },
                                    [&](Action const& a) {
                                        c.Line(a.code);
                                        c.Line();
                                    }},
                                    elt);
                                ++idx;
                            }
                            c.Line("return _0;");
                        });
                    }
                    c.Line("return tl::unexpected(std::format(\"Unexpected token {}\\n\", this->cur_token.value()));");
                });
                c.Line();
            }
        });
        });
    }

    std::string MakeArgDecl(Rule const& rule) {
        std::string res;
        for (auto it = rule.args.cbegin(), end = rule.args.cend(); it != end; ++it) {
            auto const& [type, name] = *it;
            res += fmt("{} {}", type, name);
            if (std::next(it) != end) {
                res += ", ";
            }
        }
        return res;
    }

    std::string MakeCondition(std::string_view name, Production const& prod) {
        auto first1 = g.First(prod.begin(), prod.end());
        if (first1.contains("EPS")) {
            first1.erase("EPS");
            first1.insert(g.FOLLOW[name].begin(), g.FOLLOW[name].end());
        }
        std::string res;
        for (auto it = first1.cbegin(), end = first1.cend(); it != end; ++it) {
            res += fmt("this->template Expect<{}>()", *it);
            if (std::next(it) != end) {
                res += " || ";
            }
        }
        return res;
    }

    std::string MakeArgPass(RuleRef const& rule) {
        std::string res;
        for (auto it = rule.args.cbegin(), end = rule.args.cend(); it != end; ++it) {
            res += it->code;
            if (std::next(it) != end) {
                res += ", ";
            }
        }
        return res;
    }

    #undef fmt
};