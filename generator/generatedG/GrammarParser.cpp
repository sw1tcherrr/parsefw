
// Generated from Grammar.g4 by ANTLR 4.13.1


#include "../rule.hpp"



#include "GrammarParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct GrammarParserStaticData final {
  GrammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GrammarParserStaticData(const GrammarParserStaticData&) = delete;
  GrammarParserStaticData(GrammarParserStaticData&&) = delete;
  GrammarParserStaticData& operator=(const GrammarParserStaticData&) = delete;
  GrammarParserStaticData& operator=(GrammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag grammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
GrammarParserStaticData *grammarParserStaticData = nullptr;

void grammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (grammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(grammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<GrammarParserStaticData>(
    std::vector<std::string>{
      "grammar_", "rule_", "inhList", "retList", "variants", "production", 
      "productionElement", "ruleRef", "argsList", "token", "action"
    },
    std::vector<std::string>{
      "", "'['", "']'", "'returns'", "':'", "';'", "','", "'|'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "ID", "TOKEN", "SPACE", "CODE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,11,120,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,5,0,24,8,0,10,0,12,0,27,9,0,1,0,1,
  	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,38,8,1,1,1,1,1,1,1,1,1,1,1,3,1,45,8,
  	1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,5,2,57,8,2,10,2,12,2,60,9,2,
  	1,3,1,3,1,3,1,3,1,3,5,3,67,8,3,10,3,12,3,70,9,3,1,4,1,4,1,4,5,4,75,8,
  	4,10,4,12,4,78,9,4,1,5,1,5,5,5,82,8,5,10,5,12,5,85,9,5,1,5,1,5,1,6,1,
  	6,1,6,3,6,92,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,101,8,7,1,7,1,7,1,8,
  	1,8,1,8,1,8,5,8,109,8,8,10,8,12,8,112,9,8,1,9,1,9,1,9,1,10,1,10,1,10,
  	1,10,0,0,11,0,2,4,6,8,10,12,14,16,18,20,0,0,119,0,25,1,0,0,0,2,30,1,0,
  	0,0,4,51,1,0,0,0,6,61,1,0,0,0,8,71,1,0,0,0,10,79,1,0,0,0,12,91,1,0,0,
  	0,14,93,1,0,0,0,16,104,1,0,0,0,18,113,1,0,0,0,20,116,1,0,0,0,22,24,3,
  	2,1,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,0,25,26,1,0,0,0,26,28,1,
  	0,0,0,27,25,1,0,0,0,28,29,5,0,0,1,29,1,1,0,0,0,30,31,6,1,-1,0,31,32,5,
  	8,0,0,32,37,6,1,-1,0,33,34,5,1,0,0,34,35,3,4,2,0,35,36,5,2,0,0,36,38,
  	1,0,0,0,37,33,1,0,0,0,37,38,1,0,0,0,38,44,1,0,0,0,39,40,5,3,0,0,40,41,
  	5,1,0,0,41,42,3,6,3,0,42,43,5,2,0,0,43,45,1,0,0,0,44,39,1,0,0,0,44,45,
  	1,0,0,0,45,46,1,0,0,0,46,47,5,4,0,0,47,48,3,8,4,0,48,49,6,1,-1,0,49,50,
  	5,5,0,0,50,3,1,0,0,0,51,52,5,8,0,0,52,53,5,8,0,0,53,58,6,2,-1,0,54,55,
  	5,6,0,0,55,57,3,4,2,0,56,54,1,0,0,0,57,60,1,0,0,0,58,56,1,0,0,0,58,59,
  	1,0,0,0,59,5,1,0,0,0,60,58,1,0,0,0,61,62,5,8,0,0,62,63,5,8,0,0,63,68,
  	6,3,-1,0,64,65,5,6,0,0,65,67,3,6,3,0,66,64,1,0,0,0,67,70,1,0,0,0,68,66,
  	1,0,0,0,68,69,1,0,0,0,69,7,1,0,0,0,70,68,1,0,0,0,71,76,3,10,5,0,72,73,
  	5,7,0,0,73,75,3,8,4,0,74,72,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,
  	1,0,0,0,77,9,1,0,0,0,78,76,1,0,0,0,79,83,6,5,-1,0,80,82,3,12,6,0,81,80,
  	1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,84,1,0,0,0,84,86,1,0,0,0,85,83,
  	1,0,0,0,86,87,6,5,-1,0,87,11,1,0,0,0,88,92,3,14,7,0,89,92,3,18,9,0,90,
  	92,3,20,10,0,91,88,1,0,0,0,91,89,1,0,0,0,91,90,1,0,0,0,92,13,1,0,0,0,
  	93,94,6,7,-1,0,94,95,5,8,0,0,95,100,6,7,-1,0,96,97,5,1,0,0,97,98,3,16,
  	8,0,98,99,5,2,0,0,99,101,1,0,0,0,100,96,1,0,0,0,100,101,1,0,0,0,101,102,
  	1,0,0,0,102,103,6,7,-1,0,103,15,1,0,0,0,104,105,5,11,0,0,105,110,6,8,
  	-1,0,106,107,5,6,0,0,107,109,3,16,8,0,108,106,1,0,0,0,109,112,1,0,0,0,
  	110,108,1,0,0,0,110,111,1,0,0,0,111,17,1,0,0,0,112,110,1,0,0,0,113,114,
  	5,9,0,0,114,115,6,9,-1,0,115,19,1,0,0,0,116,117,5,11,0,0,117,118,6,10,
  	-1,0,118,21,1,0,0,0,10,25,37,44,58,68,76,83,91,100,110
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  grammarParserStaticData = staticData.release();
}

}

GrammarParser::GrammarParser(TokenStream *input) : GrammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

GrammarParser::GrammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  GrammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *grammarParserStaticData->atn, grammarParserStaticData->decisionToDFA, grammarParserStaticData->sharedContextCache, options);
}

GrammarParser::~GrammarParser() {
  delete _interpreter;
}

const atn::ATN& GrammarParser::getATN() const {
  return *grammarParserStaticData->atn;
}

std::string GrammarParser::getGrammarFileName() const {
  return "Grammar.g4";
}

const std::vector<std::string>& GrammarParser::getRuleNames() const {
  return grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& GrammarParser::getVocabulary() const {
  return grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GrammarParser::getSerializedATN() const {
  return grammarParserStaticData->serializedATN;
}


//----------------- Grammar_Context ------------------------------------------------------------------

GrammarParser::Grammar_Context::Grammar_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::Grammar_Context::EOF() {
  return getToken(GrammarParser::EOF, 0);
}

std::vector<GrammarParser::Rule_Context *> GrammarParser::Grammar_Context::rule_() {
  return getRuleContexts<GrammarParser::Rule_Context>();
}

GrammarParser::Rule_Context* GrammarParser::Grammar_Context::rule_(size_t i) {
  return getRuleContext<GrammarParser::Rule_Context>(i);
}


size_t GrammarParser::Grammar_Context::getRuleIndex() const {
  return GrammarParser::RuleGrammar_;
}


GrammarParser::Grammar_Context* GrammarParser::grammar_() {
  Grammar_Context *_localctx = _tracker.createInstance<Grammar_Context>(_ctx, getState());
  enterRule(_localctx, 0, GrammarParser::RuleGrammar_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == GrammarParser::ID) {
      setState(22);
      rule_();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(28);
    match(GrammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Rule_Context ------------------------------------------------------------------

GrammarParser::Rule_Context::Rule_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* GrammarParser::Rule_Context::ID() {
  return getToken(GrammarParser::ID, 0);
}

GrammarParser::VariantsContext* GrammarParser::Rule_Context::variants() {
  return getRuleContext<GrammarParser::VariantsContext>(0);
}

GrammarParser::InhListContext* GrammarParser::Rule_Context::inhList() {
  return getRuleContext<GrammarParser::InhListContext>(0);
}

GrammarParser::RetListContext* GrammarParser::Rule_Context::retList() {
  return getRuleContext<GrammarParser::RetListContext>(0);
}


size_t GrammarParser::Rule_Context::getRuleIndex() const {
  return GrammarParser::RuleRule_;
}


GrammarParser::Rule_Context* GrammarParser::rule_() {
  Rule_Context *_localctx = _tracker.createInstance<Rule_Context>(_ctx, getState());
  enterRule(_localctx, 2, GrammarParser::RuleRule_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
     pfw::gen::Rule r; 
    setState(31);
    antlrcpp::downCast<Rule_Context *>(_localctx)->idToken = match(GrammarParser::ID);
     r.name = (antlrcpp::downCast<Rule_Context *>(_localctx)->idToken != nullptr ? antlrcpp::downCast<Rule_Context *>(_localctx)->idToken->getText() : ""); 
    setState(37);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GrammarParser::T__0) {
      setState(33);
      match(GrammarParser::T__0);
      setState(34);
      inhList(&r);
      setState(35);
      match(GrammarParser::T__1);
    }
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GrammarParser::T__2) {
      setState(39);
      match(GrammarParser::T__2);
      setState(40);
      match(GrammarParser::T__0);
      setState(41);
      retList(&r);
      setState(42);
      match(GrammarParser::T__1);
    }
    setState(46);
    match(GrammarParser::T__3);
    setState(47);
    variants(&r);
     AddRule(std::move(r)); 
    setState(49);
    match(GrammarParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InhListContext ------------------------------------------------------------------

GrammarParser::InhListContext::InhListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::InhListContext::InhListContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r)
  : ParserRuleContext(parent, invokingState) {
  this->r = r;
}

std::vector<tree::TerminalNode *> GrammarParser::InhListContext::ID() {
  return getTokens(GrammarParser::ID);
}

tree::TerminalNode* GrammarParser::InhListContext::ID(size_t i) {
  return getToken(GrammarParser::ID, i);
}

std::vector<GrammarParser::InhListContext *> GrammarParser::InhListContext::inhList() {
  return getRuleContexts<GrammarParser::InhListContext>();
}

GrammarParser::InhListContext* GrammarParser::InhListContext::inhList(size_t i) {
  return getRuleContext<GrammarParser::InhListContext>(i);
}


size_t GrammarParser::InhListContext::getRuleIndex() const {
  return GrammarParser::RuleInhList;
}


GrammarParser::InhListContext* GrammarParser::inhList(pfw::gen::Rule* r) {
  InhListContext *_localctx = _tracker.createInstance<InhListContext>(_ctx, getState(), r);
  enterRule(_localctx, 4, GrammarParser::RuleInhList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(51);
    antlrcpp::downCast<InhListContext *>(_localctx)->t = match(GrammarParser::ID);
    setState(52);
    antlrcpp::downCast<InhListContext *>(_localctx)->n = match(GrammarParser::ID);
     r->args.push_back(pfw::gen::Attribute((antlrcpp::downCast<InhListContext *>(_localctx)->t != nullptr ? antlrcpp::downCast<InhListContext *>(_localctx)->t->getText() : ""), (antlrcpp::downCast<InhListContext *>(_localctx)->n != nullptr ? antlrcpp::downCast<InhListContext *>(_localctx)->n->getText() : ""))); 
    setState(58);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(54);
        match(GrammarParser::T__5);
        setState(55);
        inhList(r); 
      }
      setState(60);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RetListContext ------------------------------------------------------------------

GrammarParser::RetListContext::RetListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::RetListContext::RetListContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r)
  : ParserRuleContext(parent, invokingState) {
  this->r = r;
}

std::vector<tree::TerminalNode *> GrammarParser::RetListContext::ID() {
  return getTokens(GrammarParser::ID);
}

tree::TerminalNode* GrammarParser::RetListContext::ID(size_t i) {
  return getToken(GrammarParser::ID, i);
}

std::vector<GrammarParser::RetListContext *> GrammarParser::RetListContext::retList() {
  return getRuleContexts<GrammarParser::RetListContext>();
}

GrammarParser::RetListContext* GrammarParser::RetListContext::retList(size_t i) {
  return getRuleContext<GrammarParser::RetListContext>(i);
}


size_t GrammarParser::RetListContext::getRuleIndex() const {
  return GrammarParser::RuleRetList;
}


GrammarParser::RetListContext* GrammarParser::retList(pfw::gen::Rule* r) {
  RetListContext *_localctx = _tracker.createInstance<RetListContext>(_ctx, getState(), r);
  enterRule(_localctx, 6, GrammarParser::RuleRetList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(61);
    antlrcpp::downCast<RetListContext *>(_localctx)->t = match(GrammarParser::ID);
    setState(62);
    antlrcpp::downCast<RetListContext *>(_localctx)->n = match(GrammarParser::ID);
     r->attrs.push_back(pfw::gen::Attribute((antlrcpp::downCast<RetListContext *>(_localctx)->t != nullptr ? antlrcpp::downCast<RetListContext *>(_localctx)->t->getText() : ""), (antlrcpp::downCast<RetListContext *>(_localctx)->n != nullptr ? antlrcpp::downCast<RetListContext *>(_localctx)->n->getText() : ""))); 
    setState(68);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(64);
        match(GrammarParser::T__5);
        setState(65);
        retList(r); 
      }
      setState(70);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariantsContext ------------------------------------------------------------------

GrammarParser::VariantsContext::VariantsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::VariantsContext::VariantsContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Rule* r)
  : ParserRuleContext(parent, invokingState) {
  this->r = r;
}

GrammarParser::ProductionContext* GrammarParser::VariantsContext::production() {
  return getRuleContext<GrammarParser::ProductionContext>(0);
}

std::vector<GrammarParser::VariantsContext *> GrammarParser::VariantsContext::variants() {
  return getRuleContexts<GrammarParser::VariantsContext>();
}

GrammarParser::VariantsContext* GrammarParser::VariantsContext::variants(size_t i) {
  return getRuleContext<GrammarParser::VariantsContext>(i);
}


size_t GrammarParser::VariantsContext::getRuleIndex() const {
  return GrammarParser::RuleVariants;
}


GrammarParser::VariantsContext* GrammarParser::variants(pfw::gen::Rule* r) {
  VariantsContext *_localctx = _tracker.createInstance<VariantsContext>(_ctx, getState(), r);
  enterRule(_localctx, 8, GrammarParser::RuleVariants);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(71);
    production(&r->variants);
    setState(76);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(72);
        match(GrammarParser::T__6);
        setState(73);
        variants(r); 
      }
      setState(78);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProductionContext ------------------------------------------------------------------

GrammarParser::ProductionContext::ProductionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ProductionContext::ProductionContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Variants* v)
  : ParserRuleContext(parent, invokingState) {
  this->v = v;
}

std::vector<GrammarParser::ProductionElementContext *> GrammarParser::ProductionContext::productionElement() {
  return getRuleContexts<GrammarParser::ProductionElementContext>();
}

GrammarParser::ProductionElementContext* GrammarParser::ProductionContext::productionElement(size_t i) {
  return getRuleContext<GrammarParser::ProductionElementContext>(i);
}


size_t GrammarParser::ProductionContext::getRuleIndex() const {
  return GrammarParser::RuleProduction;
}


GrammarParser::ProductionContext* GrammarParser::production(pfw::gen::Variants* v) {
  ProductionContext *_localctx = _tracker.createInstance<ProductionContext>(_ctx, getState(), v);
  enterRule(_localctx, 10, GrammarParser::RuleProduction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
     pfw::gen::Production p; 
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2816) != 0)) {
      setState(80);
      productionElement(&p);
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
     v->push_back(std::move(p)); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProductionElementContext ------------------------------------------------------------------

GrammarParser::ProductionElementContext::ProductionElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ProductionElementContext::ProductionElementContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p)
  : ParserRuleContext(parent, invokingState) {
  this->p = p;
}

GrammarParser::RuleRefContext* GrammarParser::ProductionElementContext::ruleRef() {
  return getRuleContext<GrammarParser::RuleRefContext>(0);
}

GrammarParser::TokenContext* GrammarParser::ProductionElementContext::token() {
  return getRuleContext<GrammarParser::TokenContext>(0);
}

GrammarParser::ActionContext* GrammarParser::ProductionElementContext::action() {
  return getRuleContext<GrammarParser::ActionContext>(0);
}


size_t GrammarParser::ProductionElementContext::getRuleIndex() const {
  return GrammarParser::RuleProductionElement;
}


GrammarParser::ProductionElementContext* GrammarParser::productionElement(pfw::gen::Production* p) {
  ProductionElementContext *_localctx = _tracker.createInstance<ProductionElementContext>(_ctx, getState(), p);
  enterRule(_localctx, 12, GrammarParser::RuleProductionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(91);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case GrammarParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(88);
        ruleRef(p);
        break;
      }

      case GrammarParser::TOKEN: {
        enterOuterAlt(_localctx, 2);
        setState(89);
        token(p);
        break;
      }

      case GrammarParser::CODE: {
        enterOuterAlt(_localctx, 3);
        setState(90);
        action(p);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleRefContext ------------------------------------------------------------------

GrammarParser::RuleRefContext::RuleRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::RuleRefContext::RuleRefContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p)
  : ParserRuleContext(parent, invokingState) {
  this->p = p;
}

tree::TerminalNode* GrammarParser::RuleRefContext::ID() {
  return getToken(GrammarParser::ID, 0);
}

GrammarParser::ArgsListContext* GrammarParser::RuleRefContext::argsList() {
  return getRuleContext<GrammarParser::ArgsListContext>(0);
}


size_t GrammarParser::RuleRefContext::getRuleIndex() const {
  return GrammarParser::RuleRuleRef;
}


GrammarParser::RuleRefContext* GrammarParser::ruleRef(pfw::gen::Production* p) {
  RuleRefContext *_localctx = _tracker.createInstance<RuleRefContext>(_ctx, getState(), p);
  enterRule(_localctx, 14, GrammarParser::RuleRuleRef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
     pfw::gen::RuleRef rr; 
    setState(94);
    antlrcpp::downCast<RuleRefContext *>(_localctx)->idToken = match(GrammarParser::ID);
     rr.name = (antlrcpp::downCast<RuleRefContext *>(_localctx)->idToken != nullptr ? antlrcpp::downCast<RuleRefContext *>(_localctx)->idToken->getText() : ""); 
    setState(100);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == GrammarParser::T__0) {
      setState(96);
      match(GrammarParser::T__0);
      setState(97);
      argsList(&rr);
      setState(98);
      match(GrammarParser::T__1);
    }
     p->push_back(std::move(rr)); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsListContext ------------------------------------------------------------------

GrammarParser::ArgsListContext::ArgsListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ArgsListContext::ArgsListContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::RuleRef* rr)
  : ParserRuleContext(parent, invokingState) {
  this->rr = rr;
}

tree::TerminalNode* GrammarParser::ArgsListContext::CODE() {
  return getToken(GrammarParser::CODE, 0);
}

std::vector<GrammarParser::ArgsListContext *> GrammarParser::ArgsListContext::argsList() {
  return getRuleContexts<GrammarParser::ArgsListContext>();
}

GrammarParser::ArgsListContext* GrammarParser::ArgsListContext::argsList(size_t i) {
  return getRuleContext<GrammarParser::ArgsListContext>(i);
}


size_t GrammarParser::ArgsListContext::getRuleIndex() const {
  return GrammarParser::RuleArgsList;
}


GrammarParser::ArgsListContext* GrammarParser::argsList(pfw::gen::RuleRef* rr) {
  ArgsListContext *_localctx = _tracker.createInstance<ArgsListContext>(_ctx, getState(), rr);
  enterRule(_localctx, 16, GrammarParser::RuleArgsList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(104);
    antlrcpp::downCast<ArgsListContext *>(_localctx)->codeToken = match(GrammarParser::CODE);
     std::string s = (antlrcpp::downCast<ArgsListContext *>(_localctx)->codeToken != nullptr ? antlrcpp::downCast<ArgsListContext *>(_localctx)->codeToken->getText() : "");
                                         rr->args.push_back(pfw::gen::Arg(std::string(s.begin() + 1, s.end() - 1))); 
    setState(110);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(106);
        match(GrammarParser::T__5);
        setState(107);
        argsList(rr); 
      }
      setState(112);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokenContext ------------------------------------------------------------------

GrammarParser::TokenContext::TokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::TokenContext::TokenContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p)
  : ParserRuleContext(parent, invokingState) {
  this->p = p;
}

tree::TerminalNode* GrammarParser::TokenContext::TOKEN() {
  return getToken(GrammarParser::TOKEN, 0);
}


size_t GrammarParser::TokenContext::getRuleIndex() const {
  return GrammarParser::RuleToken;
}


GrammarParser::TokenContext* GrammarParser::token(pfw::gen::Production* p) {
  TokenContext *_localctx = _tracker.createInstance<TokenContext>(_ctx, getState(), p);
  enterRule(_localctx, 18, GrammarParser::RuleToken);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken = match(GrammarParser::TOKEN);
     p->push_back(pfw::gen::Token((antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken != nullptr ? antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken->getText() : ""))); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionContext ------------------------------------------------------------------

GrammarParser::ActionContext::ActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

GrammarParser::ActionContext::ActionContext(ParserRuleContext *parent, size_t invokingState, pfw::gen::Production* p)
  : ParserRuleContext(parent, invokingState) {
  this->p = p;
}

tree::TerminalNode* GrammarParser::ActionContext::CODE() {
  return getToken(GrammarParser::CODE, 0);
}


size_t GrammarParser::ActionContext::getRuleIndex() const {
  return GrammarParser::RuleAction;
}


GrammarParser::ActionContext* GrammarParser::action(pfw::gen::Production* p) {
  ActionContext *_localctx = _tracker.createInstance<ActionContext>(_ctx, getState(), p);
  enterRule(_localctx, 20, GrammarParser::RuleAction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    antlrcpp::downCast<ActionContext *>(_localctx)->codeToken = match(GrammarParser::CODE);
     std::string s = (antlrcpp::downCast<ActionContext *>(_localctx)->codeToken != nullptr ? antlrcpp::downCast<ActionContext *>(_localctx)->codeToken->getText() : "");
                                         p->push_back(pfw::gen::Action(std::string(s.begin() + 1, s.end() - 1))); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void GrammarParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  grammarParserInitialize();
#else
  ::antlr4::internal::call_once(grammarParserOnceFlag, grammarParserInitialize);
#endif
}
