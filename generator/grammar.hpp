#pragma once

#include <unordered_map>
#include <unordered_set>
#include <variant>
#include "rule.hpp"
#include <pfw/util.hpp>

namespace pfw::gen {

struct Grammar {
    using RuleMap   = std::vector<Rule>;
    using FirstSet  = std::unordered_set<std::string>;
	using FirstMap  = std::unordered_map<std::string, FirstSet>;
	using FollowSet = std::unordered_set<std::string>;
	using FollowMap = std::unordered_map<std::string, FollowSet>;
	
    RuleMap rules;
	std::string start;
	FirstMap FIRST;
	FollowMap FOLLOW;

    Grammar(RuleMap&& rules, std::string_view start) : rules(std::move(rules)), start(start) {
        MakeFirst();
        MakeFollow();
    }

	FirstSet First(Production::const_iterator begin, Production::const_iterator end) {
		FirstSet res;
		if (begin == end) {
            res.insert("EPS");
            return res;
        }

		std::visit(pfw::util::overloaded {
			[&](Token const& t) {
				res.insert(t.name);		
			},
			[&](Action const& a) {
				auto suffix = First(begin + 1, end);
				res.insert(suffix.begin(), suffix.end());
			},
			[&](RuleRef const& r) {
				if (!FIRST.contains(r.name)) { return; }
				res.insert(FIRST[r.name].begin(), FIRST[r.name].end());
				if (res.contains("EPS")) {
					res.erase("EPS");
					auto suffix = First(begin + 1, end);
					res.insert(suffix.begin(), suffix.end());
				}
			}},
			*begin);
		return res;
	}

	void MakeFirst() {
		bool changed = true;
		while (changed) {
			changed = false;
			for (auto const& rule : rules) {
				auto const& name = rule.name;
				auto old_size = FIRST[name].size();
				for (auto const& production : rule.variants) {
					auto fst = First(production.begin(), production.end());
					FIRST[name].insert(fst.begin(), fst.end());
				}
				if (old_size != FIRST[name].size()) {
					changed = true;
				}
			}
		}
	}

	void MakeFollow() {
		FOLLOW[start].insert("END");
		bool changed = true;
		while (changed) {
			changed = false;
			for (auto const& rule : rules) {
				auto const& name = rule.name;
				for (auto const& production : rule.variants) {
					for (int i = 0; i < production.size(); ++i) {
						if (std::get_if<RuleRef>(&production[i]) == nullptr) { 
                            continue;
                        }
                        auto inner_rule = std::get<RuleRef>(production[i]);
						auto old_size = FOLLOW[inner_rule.name].size();

						auto suffix = First(production.begin() + i + 1, production.end());
						if (suffix.contains("EPS")) {
							suffix.erase("EPS");
							FOLLOW[inner_rule.name].insert(FOLLOW[name].begin(), FOLLOW[name].end());
						}
						FOLLOW[inner_rule.name].insert(suffix.begin(), suffix.end());
						if (old_size != FOLLOW[inner_rule.name].size()) {
							changed = true;
						}
					}
				}
			}
		}
	}
};

} // namespace pfw::gen