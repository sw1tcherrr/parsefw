
// Generated from Grammar.g4 by ANTLR 4.13.1


#include "GrammarLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct GrammarLexerStaticData final {
  GrammarLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  GrammarLexerStaticData(const GrammarLexerStaticData&) = delete;
  GrammarLexerStaticData(GrammarLexerStaticData&&) = delete;
  GrammarLexerStaticData& operator=(const GrammarLexerStaticData&) = delete;
  GrammarLexerStaticData& operator=(GrammarLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag grammarlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
GrammarLexerStaticData *grammarlexerLexerStaticData = nullptr;

void grammarlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (grammarlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(grammarlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<GrammarLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "ID", "TOKEN", 
      "SPACE", "CODE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'['", "']'", "'returns'", "':'", "';'", "','", "'|'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "ID", "TOKEN", "SPACE", "CODE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,11,72,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,1,0,1,0,1,1,1,1,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,5,7,46,8,7,10,7,
  	12,7,49,9,7,1,8,4,8,52,8,8,11,8,12,8,53,1,9,4,9,57,8,9,11,9,12,9,58,1,
  	9,1,9,1,10,1,10,1,10,5,10,66,8,10,10,10,12,10,69,9,10,1,10,1,10,0,0,11,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,1,0,5,1,0,97,122,
  	4,0,48,57,65,90,95,95,97,122,1,0,65,90,3,0,9,10,13,13,32,32,2,0,123,123,
  	125,125,76,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,
  	0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,
  	21,1,0,0,0,1,23,1,0,0,0,3,25,1,0,0,0,5,27,1,0,0,0,7,35,1,0,0,0,9,37,1,
  	0,0,0,11,39,1,0,0,0,13,41,1,0,0,0,15,43,1,0,0,0,17,51,1,0,0,0,19,56,1,
  	0,0,0,21,62,1,0,0,0,23,24,5,91,0,0,24,2,1,0,0,0,25,26,5,93,0,0,26,4,1,
  	0,0,0,27,28,5,114,0,0,28,29,5,101,0,0,29,30,5,116,0,0,30,31,5,117,0,0,
  	31,32,5,114,0,0,32,33,5,110,0,0,33,34,5,115,0,0,34,6,1,0,0,0,35,36,5,
  	58,0,0,36,8,1,0,0,0,37,38,5,59,0,0,38,10,1,0,0,0,39,40,5,44,0,0,40,12,
  	1,0,0,0,41,42,5,124,0,0,42,14,1,0,0,0,43,47,7,0,0,0,44,46,7,1,0,0,45,
  	44,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,16,1,0,0,0,49,
  	47,1,0,0,0,50,52,7,2,0,0,51,50,1,0,0,0,52,53,1,0,0,0,53,51,1,0,0,0,53,
  	54,1,0,0,0,54,18,1,0,0,0,55,57,7,3,0,0,56,55,1,0,0,0,57,58,1,0,0,0,58,
  	56,1,0,0,0,58,59,1,0,0,0,59,60,1,0,0,0,60,61,6,9,0,0,61,20,1,0,0,0,62,
  	67,5,123,0,0,63,66,3,21,10,0,64,66,8,4,0,0,65,63,1,0,0,0,65,64,1,0,0,
  	0,66,69,1,0,0,0,67,65,1,0,0,0,67,68,1,0,0,0,68,70,1,0,0,0,69,67,1,0,0,
  	0,70,71,5,125,0,0,71,22,1,0,0,0,6,0,47,53,58,65,67,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  grammarlexerLexerStaticData = staticData.release();
}

}

GrammarLexer::GrammarLexer(CharStream *input) : Lexer(input) {
  GrammarLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *grammarlexerLexerStaticData->atn, grammarlexerLexerStaticData->decisionToDFA, grammarlexerLexerStaticData->sharedContextCache);
}

GrammarLexer::~GrammarLexer() {
  delete _interpreter;
}

std::string GrammarLexer::getGrammarFileName() const {
  return "Grammar.g4";
}

const std::vector<std::string>& GrammarLexer::getRuleNames() const {
  return grammarlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& GrammarLexer::getChannelNames() const {
  return grammarlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& GrammarLexer::getModeNames() const {
  return grammarlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& GrammarLexer::getVocabulary() const {
  return grammarlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView GrammarLexer::getSerializedATN() const {
  return grammarlexerLexerStaticData->serializedATN;
}

const atn::ATN& GrammarLexer::getATN() const {
  return *grammarlexerLexerStaticData->atn;
}




void GrammarLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  grammarlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(grammarlexerLexerOnceFlag, grammarlexerLexerInitialize);
#endif
}
