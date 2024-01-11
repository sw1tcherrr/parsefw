
// Generated from Tokens.g4 by ANTLR 4.13.1


#include "TokensLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct TokensLexerStaticData final {
  TokensLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TokensLexerStaticData(const TokensLexerStaticData&) = delete;
  TokensLexerStaticData(TokensLexerStaticData&&) = delete;
  TokensLexerStaticData& operator=(const TokensLexerStaticData&) = delete;
  TokensLexerStaticData& operator=(TokensLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tokenslexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
TokensLexerStaticData *tokenslexerLexerStaticData = nullptr;

void tokenslexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tokenslexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(tokenslexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TokensLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "TOKEN", "SPACE", "CODE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "':'", "';'", "'skip'"
    },
    std::vector<std::string>{
      "", "", "", "", "TOKEN", "SPACE", "CODE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,6,44,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,1,0,
  	1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,3,4,3,24,8,3,11,3,12,3,25,1,4,4,4,29,8,
  	4,11,4,12,4,30,1,4,1,4,1,5,1,5,1,5,5,5,38,8,5,10,5,12,5,41,9,5,1,5,1,
  	5,0,0,6,1,1,3,2,5,3,7,4,9,5,11,6,1,0,3,1,0,65,90,3,0,9,10,13,13,32,32,
  	2,0,123,123,125,125,47,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,
  	0,0,9,1,0,0,0,0,11,1,0,0,0,1,13,1,0,0,0,3,15,1,0,0,0,5,17,1,0,0,0,7,23,
  	1,0,0,0,9,28,1,0,0,0,11,34,1,0,0,0,13,14,5,58,0,0,14,2,1,0,0,0,15,16,
  	5,59,0,0,16,4,1,0,0,0,17,18,5,115,0,0,18,19,5,107,0,0,19,20,5,105,0,0,
  	20,21,5,112,0,0,21,6,1,0,0,0,22,24,7,0,0,0,23,22,1,0,0,0,24,25,1,0,0,
  	0,25,23,1,0,0,0,25,26,1,0,0,0,26,8,1,0,0,0,27,29,7,1,0,0,28,27,1,0,0,
  	0,29,30,1,0,0,0,30,28,1,0,0,0,30,31,1,0,0,0,31,32,1,0,0,0,32,33,6,4,0,
  	0,33,10,1,0,0,0,34,39,5,123,0,0,35,38,3,11,5,0,36,38,8,2,0,0,37,35,1,
  	0,0,0,37,36,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,42,1,
  	0,0,0,41,39,1,0,0,0,42,43,5,125,0,0,43,12,1,0,0,0,5,0,25,30,37,39,1,6,
  	0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tokenslexerLexerStaticData = staticData.release();
}

}

TokensLexer::TokensLexer(CharStream *input) : Lexer(input) {
  TokensLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *tokenslexerLexerStaticData->atn, tokenslexerLexerStaticData->decisionToDFA, tokenslexerLexerStaticData->sharedContextCache);
}

TokensLexer::~TokensLexer() {
  delete _interpreter;
}

std::string TokensLexer::getGrammarFileName() const {
  return "Tokens.g4";
}

const std::vector<std::string>& TokensLexer::getRuleNames() const {
  return tokenslexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& TokensLexer::getChannelNames() const {
  return tokenslexerLexerStaticData->channelNames;
}

const std::vector<std::string>& TokensLexer::getModeNames() const {
  return tokenslexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& TokensLexer::getVocabulary() const {
  return tokenslexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TokensLexer::getSerializedATN() const {
  return tokenslexerLexerStaticData->serializedATN;
}

const atn::ATN& TokensLexer::getATN() const {
  return *tokenslexerLexerStaticData->atn;
}




void TokensLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tokenslexerLexerInitialize();
#else
  ::antlr4::internal::call_once(tokenslexerLexerOnceFlag, tokenslexerLexerInitialize);
#endif
}
