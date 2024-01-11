grammar Grammar;

@parser::preinclude {
#include "../rule.hpp"
}

@parser::members {
public:
std::vector<pfw::gen::Rule> rules;
std::string start;

void AddRule(pfw::gen::Rule&& r) {
    if (rules.empty()) { 
        start = r.name;
    }
    rules.push_back(std::move(r));
}
}

grammar_ : rule_* EOF ;

rule_ : { pfw::gen::Rule r; }
        ID { r.name = $ID.text; } 
        ('[' inhList[&r] ']')?
        ('returns' '[' retList[&r] ']')?
        ':'
        variants[&r]
        { AddRule(std::move(r)); }
        ';' ;

inhList [pfw::gen::Rule* r] : t=ID n=ID { r->args.push_back(pfw::gen::Attribute($t.text, $n.text)); }
                              (',' inhList[r])*  ;

retList [pfw::gen::Rule* r] : t=ID n=ID { r->attrs.push_back(pfw::gen::Attribute($t.text, $n.text)); }
                              (',' retList[r])* ;

variants [pfw::gen::Rule* r] : production[&r->variants]
                               ('|' variants[r])* ;

production [pfw::gen::Variants* v] : { pfw::gen::Production p; } 
                                     productionElement[&p]* 
                                     { v->push_back(std::move(p)); };

productionElement [pfw::gen::Production* p] : ruleRef[p] | token[p] | action[p] ;

ruleRef [pfw::gen::Production* p] : { pfw::gen::RuleRef rr; }
                                    ID { rr.name = $ID.text; }
                                    ('[' argsList[&rr] ']')? 
                                    { p->push_back(std::move(rr)); } ;

argsList [pfw::gen::RuleRef* rr] : CODE
                                   { std::string s = $CODE.text;
                                     rr->args.push_back(pfw::gen::Arg(std::string(s.begin() + 1, s.end() - 1))); }
                                   (',' argsList[rr])* 
                                   ;

token [pfw::gen::Production* p] : TOKEN { p->push_back(pfw::gen::Token($TOKEN.text)); } ;

action [pfw::gen::Production* p] : CODE
                                   { std::string s = $CODE.text;
                                     p->push_back(pfw::gen::Action(std::string(s.begin() + 1, s.end() - 1))); } ;

ID : [a-z][a-zA-Z0-9_]*;
TOKEN : [A-Z]+;
SPACE : (' '|'\r'|'\n'|'\t')+ -> skip;
CODE : '{' ( CODE | ~[{}] )* '}';
