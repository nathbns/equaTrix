
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CalcParser.
 */
class  CalcListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(CalcParser::ProgContext *ctx) = 0;
  virtual void exitProg(CalcParser::ProgContext *ctx) = 0;

  virtual void enterToTerm(CalcParser::ToTermContext *ctx) = 0;
  virtual void exitToTerm(CalcParser::ToTermContext *ctx) = 0;

  virtual void enterAddSubExpr(CalcParser::AddSubExprContext *ctx) = 0;
  virtual void exitAddSubExpr(CalcParser::AddSubExprContext *ctx) = 0;

  virtual void enterMulDivExpr(CalcParser::MulDivExprContext *ctx) = 0;
  virtual void exitMulDivExpr(CalcParser::MulDivExprContext *ctx) = 0;

  virtual void enterToPower(CalcParser::ToPowerContext *ctx) = 0;
  virtual void exitToPower(CalcParser::ToPowerContext *ctx) = 0;

  virtual void enterInfixPowExpr(CalcParser::InfixPowExprContext *ctx) = 0;
  virtual void exitInfixPowExpr(CalcParser::InfixPowExprContext *ctx) = 0;

  virtual void enterToFactor(CalcParser::ToFactorContext *ctx) = 0;
  virtual void exitToFactor(CalcParser::ToFactorContext *ctx) = 0;

  virtual void enterUnaryMinusExpr(CalcParser::UnaryMinusExprContext *ctx) = 0;
  virtual void exitUnaryMinusExpr(CalcParser::UnaryMinusExprContext *ctx) = 0;

  virtual void enterUnaryPlusExpr(CalcParser::UnaryPlusExprContext *ctx) = 0;
  virtual void exitUnaryPlusExpr(CalcParser::UnaryPlusExprContext *ctx) = 0;

  virtual void enterFunctionCallExpr(CalcParser::FunctionCallExprContext *ctx) = 0;
  virtual void exitFunctionCallExpr(CalcParser::FunctionCallExprContext *ctx) = 0;

  virtual void enterNumberExpr(CalcParser::NumberExprContext *ctx) = 0;
  virtual void exitNumberExpr(CalcParser::NumberExprContext *ctx) = 0;

  virtual void enterIdExpr(CalcParser::IdExprContext *ctx) = 0;
  virtual void exitIdExpr(CalcParser::IdExprContext *ctx) = 0;

  virtual void enterParenExpr(CalcParser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(CalcParser::ParenExprContext *ctx) = 0;

  virtual void enterFunc(CalcParser::FuncContext *ctx) = 0;
  virtual void exitFunc(CalcParser::FuncContext *ctx) = 0;


};

