
// Generated from Tokens.g4 by ANTLR 4.13.1





#include "TokensParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TokensParserStaticData final {
  TokensParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TokensParserStaticData(const TokensParserStaticData&) = delete;
  TokensParserStaticData(TokensParserStaticData&&) = delete;
  TokensParserStaticData& operator=(const TokensParserStaticData&) = delete;
  TokensParserStaticData& operator=(TokensParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tokensParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
TokensParserStaticData *tokensParserStaticData = nullptr;

void tokensParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tokensParserStaticData != nullptr) {
    return;
  }
#else
  assert(tokensParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TokensParserStaticData>(
    std::vector<std::string>{
      "grammar_", "token", "skip"
    },
    std::vector<std::string>{
      "", "':'", "';'", "'skip'"
    },
    std::vector<std::string>{
      "", "", "", "", "TOKEN", "SPACE", "CODE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,6,30,2,0,7,0,2,1,7,1,2,2,7,2,1,0,5,0,8,8,0,10,0,12,0,11,9,0,1,0,3,
  	0,14,8,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	0,0,3,0,2,4,0,0,28,0,9,1,0,0,0,2,17,1,0,0,0,4,23,1,0,0,0,6,8,3,2,1,0,
  	7,6,1,0,0,0,8,11,1,0,0,0,9,7,1,0,0,0,9,10,1,0,0,0,10,13,1,0,0,0,11,9,
  	1,0,0,0,12,14,3,4,2,0,13,12,1,0,0,0,13,14,1,0,0,0,14,15,1,0,0,0,15,16,
  	5,0,0,1,16,1,1,0,0,0,17,18,5,4,0,0,18,19,5,1,0,0,19,20,5,6,0,0,20,21,
  	5,2,0,0,21,22,6,1,-1,0,22,3,1,0,0,0,23,24,5,3,0,0,24,25,5,1,0,0,25,26,
  	5,6,0,0,26,27,5,2,0,0,27,28,6,2,-1,0,28,5,1,0,0,0,2,9,13
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tokensParserStaticData = staticData.release();
}

}

TokensParser::TokensParser(TokenStream *input) : TokensParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TokensParser::TokensParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TokensParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *tokensParserStaticData->atn, tokensParserStaticData->decisionToDFA, tokensParserStaticData->sharedContextCache, options);
}

TokensParser::~TokensParser() {
  delete _interpreter;
}

const atn::ATN& TokensParser::getATN() const {
  return *tokensParserStaticData->atn;
}

std::string TokensParser::getGrammarFileName() const {
  return "Tokens.g4";
}

const std::vector<std::string>& TokensParser::getRuleNames() const {
  return tokensParserStaticData->ruleNames;
}

const dfa::Vocabulary& TokensParser::getVocabulary() const {
  return tokensParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TokensParser::getSerializedATN() const {
  return tokensParserStaticData->serializedATN;
}


//----------------- Grammar_Context ------------------------------------------------------------------

TokensParser::Grammar_Context::Grammar_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TokensParser::Grammar_Context::EOF() {
  return getToken(TokensParser::EOF, 0);
}

std::vector<TokensParser::TokenContext *> TokensParser::Grammar_Context::token() {
  return getRuleContexts<TokensParser::TokenContext>();
}

TokensParser::TokenContext* TokensParser::Grammar_Context::token(size_t i) {
  return getRuleContext<TokensParser::TokenContext>(i);
}

TokensParser::SkipContext* TokensParser::Grammar_Context::skip() {
  return getRuleContext<TokensParser::SkipContext>(0);
}


size_t TokensParser::Grammar_Context::getRuleIndex() const {
  return TokensParser::RuleGrammar_;
}


TokensParser::Grammar_Context* TokensParser::grammar_() {
  Grammar_Context *_localctx = _tracker.createInstance<Grammar_Context>(_ctx, getState());
  enterRule(_localctx, 0, TokensParser::RuleGrammar_);
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
    setState(9);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TokensParser::TOKEN) {
      setState(6);
      token();
      setState(11);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(13);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TokensParser::T__2) {
      setState(12);
      skip();
    }
    setState(15);
    match(TokensParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TokenContext ------------------------------------------------------------------

TokensParser::TokenContext::TokenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TokensParser::TokenContext::TOKEN() {
  return getToken(TokensParser::TOKEN, 0);
}

tree::TerminalNode* TokensParser::TokenContext::CODE() {
  return getToken(TokensParser::CODE, 0);
}


size_t TokensParser::TokenContext::getRuleIndex() const {
  return TokensParser::RuleToken;
}


TokensParser::TokenContext* TokensParser::token() {
  TokenContext *_localctx = _tracker.createInstance<TokenContext>(_ctx, getState());
  enterRule(_localctx, 2, TokensParser::RuleToken);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17);
    antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken = match(TokensParser::TOKEN);
    setState(18);
    match(TokensParser::T__0);
    setState(19);
    antlrcpp::downCast<TokenContext *>(_localctx)->codeToken = match(TokensParser::CODE);
    setState(20);
    match(TokensParser::T__1);
     std::string s = (antlrcpp::downCast<TokenContext *>(_localctx)->codeToken != nullptr ? antlrcpp::downCast<TokenContext *>(_localctx)->codeToken->getText() : "");
              map.emplace_back((antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken != nullptr ? antlrcpp::downCast<TokenContext *>(_localctx)->tokenToken->getText() : ""), std::string(s.begin() + 1, s.end() - 1)); 
            
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SkipContext ------------------------------------------------------------------

TokensParser::SkipContext::SkipContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TokensParser::SkipContext::CODE() {
  return getToken(TokensParser::CODE, 0);
}


size_t TokensParser::SkipContext::getRuleIndex() const {
  return TokensParser::RuleSkip;
}


TokensParser::SkipContext* TokensParser::skip() {
  SkipContext *_localctx = _tracker.createInstance<SkipContext>(_ctx, getState());
  enterRule(_localctx, 4, TokensParser::RuleSkip);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(23);
    match(TokensParser::T__2);
    setState(24);
    match(TokensParser::T__0);
    setState(25);
    antlrcpp::downCast<SkipContext *>(_localctx)->codeToken = match(TokensParser::CODE);
    setState(26);
    match(TokensParser::T__1);
     std::string s = (antlrcpp::downCast<SkipContext *>(_localctx)->codeToken != nullptr ? antlrcpp::downCast<SkipContext *>(_localctx)->codeToken->getText() : "");
             skip_predicate = std::string(s.begin() + 1, s.end() - 1);
           
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void TokensParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tokensParserInitialize();
#else
  ::antlr4::internal::call_once(tokensParserOnceFlag, tokensParserInitialize);
#endif
}
