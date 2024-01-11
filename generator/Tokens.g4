grammar Tokens;

@parser::preinclude {
}

@parser::members {
public:
std::vector<std::pair<std::string, std::string>> map;
std::string skip_predicate;

}

grammar_ : token* skip? EOF ;

token : TOKEN ':'
        CODE ';' 
        { std::string s = $CODE.text;
          map.emplace_back($TOKEN.text, std::string(s.begin() + 1, s.end() - 1)); 
        }
        ;

skip : 'skip' ':' CODE ';'
       { std::string s = $CODE.text;
         skip_predicate = std::string(s.begin() + 1, s.end() - 1);
       } ;

TOKEN : [A-Z]+;
SPACE : (' '|'\r'|'\n'|'\t')+ -> skip;
CODE : '{' ( CODE | ~[{}] )* '}';
