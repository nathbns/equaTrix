
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcListener.h"
#include "CalcVisitor.h"

#include "CalcParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CalcParserStaticData final {
  CalcParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcParserStaticData(const CalcParserStaticData&) = delete;
  CalcParserStaticData(CalcParserStaticData&&) = delete;
  CalcParserStaticData& operator=(const CalcParserStaticData&) = delete;
  CalcParserStaticData& operator=(CalcParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calcParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcParserStaticData> calcParserStaticData = nullptr;

void calcParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calcParserStaticData != nullptr) {
    return;
  }
#else
  assert(calcParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcParserStaticData>(
    std::vector<std::string>{
      "prog", "expr", "term", "power", "factor", "func"
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
  	4,1,20,68,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,1,0,1,0,
  	1,1,1,1,1,1,1,1,1,1,1,1,5,1,22,8,1,10,1,12,1,25,9,1,1,2,1,2,1,2,1,2,1,
  	2,1,2,5,2,33,8,2,10,2,12,2,36,9,2,1,3,1,3,1,3,1,3,1,3,1,3,5,3,44,8,3,
  	10,3,12,3,47,9,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,3,4,64,8,4,1,5,1,5,1,5,0,3,2,4,6,6,0,2,4,6,8,10,0,3,1,0,1,2,1,
  	0,3,4,1,0,8,17,69,0,12,1,0,0,0,2,15,1,0,0,0,4,26,1,0,0,0,6,37,1,0,0,0,
  	8,63,1,0,0,0,10,65,1,0,0,0,12,13,3,2,1,0,13,14,5,0,0,1,14,1,1,0,0,0,15,
  	16,6,1,-1,0,16,17,3,4,2,0,17,23,1,0,0,0,18,19,10,2,0,0,19,20,7,0,0,0,
  	20,22,3,4,2,0,21,18,1,0,0,0,22,25,1,0,0,0,23,21,1,0,0,0,23,24,1,0,0,0,
  	24,3,1,0,0,0,25,23,1,0,0,0,26,27,6,2,-1,0,27,28,3,6,3,0,28,34,1,0,0,0,
  	29,30,10,2,0,0,30,31,7,1,0,0,31,33,3,6,3,0,32,29,1,0,0,0,33,36,1,0,0,
  	0,34,32,1,0,0,0,34,35,1,0,0,0,35,5,1,0,0,0,36,34,1,0,0,0,37,38,6,3,-1,
  	0,38,39,3,8,4,0,39,45,1,0,0,0,40,41,10,2,0,0,41,42,5,5,0,0,42,44,3,8,
  	4,0,43,40,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,7,1,0,
  	0,0,47,45,1,0,0,0,48,49,5,2,0,0,49,64,3,8,4,0,50,51,5,1,0,0,51,64,3,8,
  	4,0,52,53,3,10,5,0,53,54,5,6,0,0,54,55,3,2,1,0,55,56,5,7,0,0,56,64,1,
  	0,0,0,57,64,5,18,0,0,58,64,5,19,0,0,59,60,5,6,0,0,60,61,3,2,1,0,61,62,
  	5,7,0,0,62,64,1,0,0,0,63,48,1,0,0,0,63,50,1,0,0,0,63,52,1,0,0,0,63,57,
  	1,0,0,0,63,58,1,0,0,0,63,59,1,0,0,0,64,9,1,0,0,0,65,66,7,2,0,0,66,11,
  	1,0,0,0,4,23,34,45,63
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calcParserStaticData = std::move(staticData);
}

}

CalcParser::CalcParser(TokenStream *input) : CalcParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CalcParser::CalcParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CalcParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *calcParserStaticData->atn, calcParserStaticData->decisionToDFA, calcParserStaticData->sharedContextCache, options);
}

CalcParser::~CalcParser() {
  delete _interpreter;
}

const atn::ATN& CalcParser::getATN() const {
  return *calcParserStaticData->atn;
}

std::string CalcParser::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcParser::getRuleNames() const {
  return calcParserStaticData->ruleNames;
}

const dfa::Vocabulary& CalcParser::getVocabulary() const {
  return calcParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcParser::getSerializedATN() const {
  return calcParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

CalcParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalcParser::ExprContext* CalcParser::ProgContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::ProgContext::EOF() {
  return getToken(CalcParser::EOF, 0);
}


size_t CalcParser::ProgContext::getRuleIndex() const {
  return CalcParser::RuleProg;
}

void CalcParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void CalcParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


std::any CalcParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ProgContext* CalcParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, CalcParser::RuleProg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    expr(0);
    setState(13);
    match(CalcParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CalcParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::ExprContext::getRuleIndex() const {
  return CalcParser::RuleExpr;
}

void CalcParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ToTermContext ------------------------------------------------------------------

CalcParser::TermContext* CalcParser::ToTermContext::term() {
  return getRuleContext<CalcParser::TermContext>(0);
}

CalcParser::ToTermContext::ToTermContext(ExprContext *ctx) { copyFrom(ctx); }

void CalcParser::ToTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterToTerm(this);
}
void CalcParser::ToTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitToTerm(this);
}

std::any CalcParser::ToTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitToTerm(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExprContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::AddSubExprContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::TermContext* CalcParser::AddSubExprContext::term() {
  return getRuleContext<CalcParser::TermContext>(0);
}

CalcParser::AddSubExprContext::AddSubExprContext(ExprContext *ctx) { copyFrom(ctx); }

void CalcParser::AddSubExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddSubExpr(this);
}
void CalcParser::AddSubExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddSubExpr(this);
}

std::any CalcParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ExprContext* CalcParser::expr() {
   return expr(0);
}

CalcParser::ExprContext* CalcParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalcParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  CalcParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, CalcParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToTermContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(16);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(23);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleExpr);
        setState(18);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(19);
        antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == CalcParser::T__0

        || _la == CalcParser::T__1)) {
          antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(20);
        term(0); 
      }
      setState(25);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

CalcParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::TermContext::getRuleIndex() const {
  return CalcParser::RuleTerm;
}

void CalcParser::TermContext::copyFrom(TermContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MulDivExprContext ------------------------------------------------------------------

CalcParser::TermContext* CalcParser::MulDivExprContext::term() {
  return getRuleContext<CalcParser::TermContext>(0);
}

CalcParser::PowerContext* CalcParser::MulDivExprContext::power() {
  return getRuleContext<CalcParser::PowerContext>(0);
}

CalcParser::MulDivExprContext::MulDivExprContext(TermContext *ctx) { copyFrom(ctx); }

void CalcParser::MulDivExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulDivExpr(this);
}
void CalcParser::MulDivExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulDivExpr(this);
}

std::any CalcParser::MulDivExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitMulDivExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToPowerContext ------------------------------------------------------------------

CalcParser::PowerContext* CalcParser::ToPowerContext::power() {
  return getRuleContext<CalcParser::PowerContext>(0);
}

CalcParser::ToPowerContext::ToPowerContext(TermContext *ctx) { copyFrom(ctx); }

void CalcParser::ToPowerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterToPower(this);
}
void CalcParser::ToPowerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitToPower(this);
}

std::any CalcParser::ToPowerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitToPower(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::TermContext* CalcParser::term() {
   return term(0);
}

CalcParser::TermContext* CalcParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalcParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  CalcParser::TermContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, CalcParser::RuleTerm, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToPowerContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(27);
    power(0);
    _ctx->stop = _input->LT(-1);
    setState(34);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<MulDivExprContext>(_tracker.createInstance<TermContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleTerm);
        setState(29);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(30);
        antlrcpp::downCast<MulDivExprContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == CalcParser::T__2

        || _la == CalcParser::T__3)) {
          antlrcpp::downCast<MulDivExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(31);
        power(0); 
      }
      setState(36);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PowerContext ------------------------------------------------------------------

CalcParser::PowerContext::PowerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::PowerContext::getRuleIndex() const {
  return CalcParser::RulePower;
}

void CalcParser::PowerContext::copyFrom(PowerContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InfixPowExprContext ------------------------------------------------------------------

CalcParser::PowerContext* CalcParser::InfixPowExprContext::power() {
  return getRuleContext<CalcParser::PowerContext>(0);
}

CalcParser::FactorContext* CalcParser::InfixPowExprContext::factor() {
  return getRuleContext<CalcParser::FactorContext>(0);
}

CalcParser::InfixPowExprContext::InfixPowExprContext(PowerContext *ctx) { copyFrom(ctx); }

void CalcParser::InfixPowExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInfixPowExpr(this);
}
void CalcParser::InfixPowExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInfixPowExpr(this);
}

std::any CalcParser::InfixPowExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitInfixPowExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ToFactorContext ------------------------------------------------------------------

CalcParser::FactorContext* CalcParser::ToFactorContext::factor() {
  return getRuleContext<CalcParser::FactorContext>(0);
}

CalcParser::ToFactorContext::ToFactorContext(PowerContext *ctx) { copyFrom(ctx); }

void CalcParser::ToFactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterToFactor(this);
}
void CalcParser::ToFactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitToFactor(this);
}

std::any CalcParser::ToFactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitToFactor(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::PowerContext* CalcParser::power() {
   return power(0);
}

CalcParser::PowerContext* CalcParser::power(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalcParser::PowerContext *_localctx = _tracker.createInstance<PowerContext>(_ctx, parentState);
  CalcParser::PowerContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 6;
  enterRecursionRule(_localctx, 6, CalcParser::RulePower, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<ToFactorContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(38);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(45);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<InfixPowExprContext>(_tracker.createInstance<PowerContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RulePower);
        setState(40);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(41);
        match(CalcParser::T__4);
        setState(42);
        factor(); 
      }
      setState(47);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

CalcParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::FactorContext::getRuleIndex() const {
  return CalcParser::RuleFactor;
}

void CalcParser::FactorContext::copyFrom(FactorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FunctionCallExprContext ------------------------------------------------------------------

CalcParser::FuncContext* CalcParser::FunctionCallExprContext::func() {
  return getRuleContext<CalcParser::FuncContext>(0);
}

CalcParser::ExprContext* CalcParser::FunctionCallExprContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::FunctionCallExprContext::FunctionCallExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::FunctionCallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpr(this);
}
void CalcParser::FunctionCallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpr(this);
}

std::any CalcParser::FunctionCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitFunctionCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::IdExprContext::IDX() {
  return getToken(CalcParser::IDX, 0);
}

CalcParser::IdExprContext::IdExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::IdExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdExpr(this);
}
void CalcParser::IdExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdExpr(this);
}

std::any CalcParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberExprContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::NumberExprContext::NUMBER() {
  return getToken(CalcParser::NUMBER, 0);
}

CalcParser::NumberExprContext::NumberExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::NumberExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberExpr(this);
}
void CalcParser::NumberExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberExpr(this);
}

std::any CalcParser::NumberExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitNumberExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryPlusExprContext ------------------------------------------------------------------

CalcParser::FactorContext* CalcParser::UnaryPlusExprContext::factor() {
  return getRuleContext<CalcParser::FactorContext>(0);
}

CalcParser::UnaryPlusExprContext::UnaryPlusExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::UnaryPlusExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryPlusExpr(this);
}
void CalcParser::UnaryPlusExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryPlusExpr(this);
}

std::any CalcParser::UnaryPlusExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitUnaryPlusExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::ParenExprContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::ParenExprContext::ParenExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::ParenExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpr(this);
}
void CalcParser::ParenExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpr(this);
}

std::any CalcParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryMinusExprContext ------------------------------------------------------------------

CalcParser::FactorContext* CalcParser::UnaryMinusExprContext::factor() {
  return getRuleContext<CalcParser::FactorContext>(0);
}

CalcParser::UnaryMinusExprContext::UnaryMinusExprContext(FactorContext *ctx) { copyFrom(ctx); }

void CalcParser::UnaryMinusExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryMinusExpr(this);
}
void CalcParser::UnaryMinusExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryMinusExpr(this);
}

std::any CalcParser::UnaryMinusExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitUnaryMinusExpr(this);
  else
    return visitor->visitChildren(this);
}
CalcParser::FactorContext* CalcParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 8, CalcParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(63);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalcParser::T__1: {
        _localctx = _tracker.createInstance<CalcParser::UnaryMinusExprContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(48);
        match(CalcParser::T__1);
        setState(49);
        factor();
        break;
      }

      case CalcParser::T__0: {
        _localctx = _tracker.createInstance<CalcParser::UnaryPlusExprContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(50);
        match(CalcParser::T__0);
        setState(51);
        factor();
        break;
      }

      case CalcParser::T__7:
      case CalcParser::T__8:
      case CalcParser::T__9:
      case CalcParser::T__10:
      case CalcParser::T__11:
      case CalcParser::T__12:
      case CalcParser::T__13:
      case CalcParser::T__14:
      case CalcParser::T__15:
      case CalcParser::T__16: {
        _localctx = _tracker.createInstance<CalcParser::FunctionCallExprContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(52);
        func();
        setState(53);
        match(CalcParser::T__5);
        setState(54);
        expr(0);
        setState(55);
        match(CalcParser::T__6);
        break;
      }

      case CalcParser::NUMBER: {
        _localctx = _tracker.createInstance<CalcParser::NumberExprContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(57);
        match(CalcParser::NUMBER);
        break;
      }

      case CalcParser::IDX: {
        _localctx = _tracker.createInstance<CalcParser::IdExprContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(58);
        match(CalcParser::IDX);
        break;
      }

      case CalcParser::T__5: {
        _localctx = _tracker.createInstance<CalcParser::ParenExprContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(59);
        match(CalcParser::T__5);
        setState(60);
        expr(0);
        setState(61);
        match(CalcParser::T__6);
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

//----------------- FuncContext ------------------------------------------------------------------

CalcParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::FuncContext::getRuleIndex() const {
  return CalcParser::RuleFunc;
}

void CalcParser::FuncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc(this);
}

void CalcParser::FuncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CalcListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc(this);
}


std::any CalcParser::FuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitFunc(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::FuncContext* CalcParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 10, CalcParser::RuleFunc);
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
    setState(65);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 261888) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CalcParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 2: return termSempred(antlrcpp::downCast<TermContext *>(context), predicateIndex);
    case 3: return powerSempred(antlrcpp::downCast<PowerContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CalcParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CalcParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CalcParser::powerSempred(PowerContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void CalcParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calcParserInitialize();
#else
  ::antlr4::internal::call_once(calcParserOnceFlag, calcParserInitialize);
#endif
}
