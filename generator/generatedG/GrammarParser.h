
// Generated from Grammar.g4 by ANTLR 4.13.1

#pragma once


#include "../rule.hpp"


#include "antlr4-runtime.h"




class  GrammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    ID = 8, TOKEN = 9, SPACE = 10, CODE = 11
  };

  enum {
    RuleGrammar_ = 0, RuleRule_ = 1, RuleInhList = 2, RuleRetList = 3, RuleVariants = 4, 
    RuleProduction = 5, RuleProductionElement = 6, RuleRuleRef = 7, RuleArgsList = 8, 
    RuleToken = 9, RuleAction = 10
  };

  explicit GrammarParser(antlr4::TokenStream *input);

  GrammarParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~GrammarParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  public:
  std::vector<pfw::gen::Rule> rules;
  std::string start;

  void AddRule(pfw::gen::Rule&& r) {
      if (rules.empty()) { 
          start = r.name;
      }
      rules.push_back(std::move(r));
  }


  class Grammar_Context;
  class Rule_Context;
  class InhListContext;
  class RetListContext;
  class VariantsContext;
  class ProductionContext;
  class ProductionElementContext;
  class RuleRefContext;
  class ArgsListContext;
  class TokenContext;
  class ActionContext; 

  class  Grammar_Context : public antlr4::ParserRuleContext {
  public:
    Grammar_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Rule_Context *> rule_();
    Rule_Context* rule_(size_t i);

   
  };

  Grammar_Context* grammar_();

  class  Rule_Context : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *idToken = nullptr;
    Rule_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    VariantsContext *variants();
    InhListContext *inhList();
    RetListContext *retList();

   
  };

  Rule_Context* rule_();

  class  InhListContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Rule* r;
    antlr4::Token *t = nullptr;
    antlr4::Token *n = nullptr;
    InhListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    InhListContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<InhListContext *> inhList();
    InhListContext* inhList(size_t i);

   
  };

  InhListContext* inhList(pfw::gen::Rule* r);

  class  RetListContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Rule* r;
    antlr4::Token *t = nullptr;
    antlr4::Token *n = nullptr;
    RetListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    RetListContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<RetListContext *> retList();
    RetListContext* retList(size_t i);

   
  };

  RetListContext* retList(pfw::gen::Rule* r);

  class  VariantsContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Rule* r;
    VariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    VariantsContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r);
    virtual size_t getRuleIndex() const override;
    ProductionContext *production();
    std::vector<VariantsContext *> variants();
    VariantsContext* variants(size_t i);

   
  };

  VariantsContext* variants(pfw::gen::Rule* r);

  class  ProductionContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Variants* v;
    ProductionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    ProductionContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Variants* v);
    virtual size_t getRuleIndex() const override;
    std::vector<ProductionElementContext *> productionElement();
    ProductionElementContext* productionElement(size_t i);

   
  };

  ProductionContext* production(pfw::gen::Variants* v);

  class  ProductionElementContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Production* p;
    ProductionElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    ProductionElementContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p);
    virtual size_t getRuleIndex() const override;
    RuleRefContext *ruleRef();
    TokenContext *token();
    ActionContext *action();

   
  };

  ProductionElementContext* productionElement(pfw::gen::Production* p);

  class  RuleRefContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Production* p;
    antlr4::Token *idToken = nullptr;
    RuleRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    RuleRefContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ArgsListContext *argsList();

   
  };

  RuleRefContext* ruleRef(pfw::gen::Production* p);

  class  ArgsListContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::RuleRef* rr;
    antlr4::Token *codeToken = nullptr;
    ArgsListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    ArgsListContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::RuleRef* rr);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODE();
    std::vector<ArgsListContext *> argsList();
    ArgsListContext* argsList(size_t i);

   
  };

  ArgsListContext* argsList(pfw::gen::RuleRef* rr);

  class  TokenContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Production* p;
    antlr4::Token *tokenToken = nullptr;
    TokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    TokenContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TOKEN();

   
  };

  TokenContext* token(pfw::gen::Production* p);

  class  ActionContext : public antlr4::ParserRuleContext {
  public:
    pfw::gen::Production* p;
    antlr4::Token *codeToken = nullptr;
    ActionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    ActionContext(antlr4::ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODE();

   
  };

  ActionContext* action(pfw::gen::Production* p);


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

