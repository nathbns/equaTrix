
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CalcLexerStaticData final {
  CalcLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcLexerStaticData(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData(CalcLexerStaticData&&) = delete;
  CalcLexerStaticData& operator=(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData& operator=(CalcLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag calclexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcLexerStaticData> calclexerLexerStaticData = nullptr;

void calclexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calclexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(calclexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "NUMBER", "IDX", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'+'", "'-'", "'*'", "'/'", "'^'", "'('", "')'", "'sin'", "'cos'", 
      "'tan'", "'arctan'", "'arcsin'", "'arccos'", "'ln'", "'log'", "'exp'", 
      "'sqrt'", "", "'x'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "NUMBER", "IDX", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,20,126,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,1,0,1,1,1,
  	1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,
  	1,8,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,
  	1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,
  	4,17,106,8,17,11,17,12,17,107,1,17,1,17,4,17,112,8,17,11,17,12,17,113,
  	3,17,116,8,17,1,18,1,18,1,19,4,19,121,8,19,11,19,12,19,122,1,19,1,19,
  	0,0,20,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,
  	27,14,29,15,31,16,33,17,35,18,37,19,39,20,1,0,2,1,0,48,57,3,0,9,10,13,
  	13,32,32,129,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,1,41,1,0,
  	0,0,3,43,1,0,0,0,5,45,1,0,0,0,7,47,1,0,0,0,9,49,1,0,0,0,11,51,1,0,0,0,
  	13,53,1,0,0,0,15,55,1,0,0,0,17,59,1,0,0,0,19,63,1,0,0,0,21,67,1,0,0,0,
  	23,74,1,0,0,0,25,81,1,0,0,0,27,88,1,0,0,0,29,91,1,0,0,0,31,95,1,0,0,0,
  	33,99,1,0,0,0,35,105,1,0,0,0,37,117,1,0,0,0,39,120,1,0,0,0,41,42,5,43,
  	0,0,42,2,1,0,0,0,43,44,5,45,0,0,44,4,1,0,0,0,45,46,5,42,0,0,46,6,1,0,
  	0,0,47,48,5,47,0,0,48,8,1,0,0,0,49,50,5,94,0,0,50,10,1,0,0,0,51,52,5,
  	40,0,0,52,12,1,0,0,0,53,54,5,41,0,0,54,14,1,0,0,0,55,56,5,115,0,0,56,
  	57,5,105,0,0,57,58,5,110,0,0,58,16,1,0,0,0,59,60,5,99,0,0,60,61,5,111,
  	0,0,61,62,5,115,0,0,62,18,1,0,0,0,63,64,5,116,0,0,64,65,5,97,0,0,65,66,
  	5,110,0,0,66,20,1,0,0,0,67,68,5,97,0,0,68,69,5,114,0,0,69,70,5,99,0,0,
  	70,71,5,116,0,0,71,72,5,97,0,0,72,73,5,110,0,0,73,22,1,0,0,0,74,75,5,
  	97,0,0,75,76,5,114,0,0,76,77,5,99,0,0,77,78,5,115,0,0,78,79,5,105,0,0,
  	79,80,5,110,0,0,80,24,1,0,0,0,81,82,5,97,0,0,82,83,5,114,0,0,83,84,5,
  	99,0,0,84,85,5,99,0,0,85,86,5,111,0,0,86,87,5,115,0,0,87,26,1,0,0,0,88,
  	89,5,108,0,0,89,90,5,110,0,0,90,28,1,0,0,0,91,92,5,108,0,0,92,93,5,111,
  	0,0,93,94,5,103,0,0,94,30,1,0,0,0,95,96,5,101,0,0,96,97,5,120,0,0,97,
  	98,5,112,0,0,98,32,1,0,0,0,99,100,5,115,0,0,100,101,5,113,0,0,101,102,
  	5,114,0,0,102,103,5,116,0,0,103,34,1,0,0,0,104,106,7,0,0,0,105,104,1,
  	0,0,0,106,107,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,115,1,0,0,0,
  	109,111,5,46,0,0,110,112,7,0,0,0,111,110,1,0,0,0,112,113,1,0,0,0,113,
  	111,1,0,0,0,113,114,1,0,0,0,114,116,1,0,0,0,115,109,1,0,0,0,115,116,1,
  	0,0,0,116,36,1,0,0,0,117,118,5,120,0,0,118,38,1,0,0,0,119,121,7,1,0,0,
  	120,119,1,0,0,0,121,122,1,0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,124,
  	1,0,0,0,124,125,6,19,0,0,125,40,1,0,0,0,5,0,107,113,115,122,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calclexerLexerStaticData = std::move(staticData);
}

}

CalcLexer::CalcLexer(CharStream *input) : Lexer(input) {
  CalcLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *calclexerLexerStaticData->atn, calclexerLexerStaticData->decisionToDFA, calclexerLexerStaticData->sharedContextCache);
}

CalcLexer::~CalcLexer() {
  delete _interpreter;
}

std::string CalcLexer::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcLexer::getRuleNames() const {
  return calclexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CalcLexer::getChannelNames() const {
  return calclexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CalcLexer::getModeNames() const {
  return calclexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CalcLexer::getVocabulary() const {
  return calclexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcLexer::getSerializedATN() const {
  return calclexerLexerStaticData->serializedATN;
}

const atn::ATN& CalcLexer::getATN() const {
  return *calclexerLexerStaticData->atn;
}




void CalcLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calclexerLexerInitialize();
#else
  ::antlr4::internal::call_once(calclexerLexerOnceFlag, calclexerLexerInitialize);
#endif
}
