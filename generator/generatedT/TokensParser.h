
// Generated from Tokens.g4 by ANTLR 4.13.1

#pragma once




#include "antlr4-runtime.h"




class  TokensParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, TOKEN = 4, SPACE = 5, CODE = 6
  };

  enum {
    RuleGrammar_ = 0, RuleToken = 1, RuleSkip = 2
  };

  explicit TokensParser(antlr4::TokenStream *input);

  TokensParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~TokensParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  public:
  std::vector<std::pair<std::string, std::string>> map;
  std::string skip_predicate;



  class Grammar_Context;
  class TokenContext;
  class SkipContext; 

  class  Grammar_Context : public antlr4::ParserRuleContext {
  public:
    Grammar_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<TokenContext *> token();
    TokenContext* token(size_t i);
    SkipContext *skip();

   
  };

  Grammar_Context* grammar_();

  class  TokenContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *tokenToken = nullptr;
    antlr4::Token *codeToken = nullptr;
    TokenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TOKEN();
    antlr4::tree::TerminalNode *CODE();

   
  };

  TokenContext* token();

  class  SkipContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *codeToken = nullptr;
    SkipContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CODE();

   
  };

  SkipContext* skip();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

