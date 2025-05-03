
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcListener.h"


/**
 * This class provides an empty implementation of CalcListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CalcBaseListener : public CalcListener {
public:

  virtual void enterProg(CalcParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(CalcParser::ProgContext * /*ctx*/) override { }

  virtual void enterToTerm(CalcParser::ToTermContext * /*ctx*/) override { }
  virtual void exitToTerm(CalcParser::ToTermContext * /*ctx*/) override { }

  virtual void enterAddSubExpr(CalcParser::AddSubExprContext * /*ctx*/) override { }
  virtual void exitAddSubExpr(CalcParser::AddSubExprContext * /*ctx*/) override { }

  virtual void enterMulDivExpr(CalcParser::MulDivExprContext * /*ctx*/) override { }
  virtual void exitMulDivExpr(CalcParser::MulDivExprContext * /*ctx*/) override { }

  virtual void enterToPower(CalcParser::ToPowerContext * /*ctx*/) override { }
  virtual void exitToPower(CalcParser::ToPowerContext * /*ctx*/) override { }

  virtual void enterInfixPowExpr(CalcParser::InfixPowExprContext * /*ctx*/) override { }
  virtual void exitInfixPowExpr(CalcParser::InfixPowExprContext * /*ctx*/) override { }

  virtual void enterToFactor(CalcParser::ToFactorContext * /*ctx*/) override { }
  virtual void exitToFactor(CalcParser::ToFactorContext * /*ctx*/) override { }

  virtual void enterUnaryMinusExpr(CalcParser::UnaryMinusExprContext * /*ctx*/) override { }
  virtual void exitUnaryMinusExpr(CalcParser::UnaryMinusExprContext * /*ctx*/) override { }

  virtual void enterUnaryPlusExpr(CalcParser::UnaryPlusExprContext * /*ctx*/) override { }
  virtual void exitUnaryPlusExpr(CalcParser::UnaryPlusExprContext * /*ctx*/) override { }

  virtual void enterFunctionCallExpr(CalcParser::FunctionCallExprContext * /*ctx*/) override { }
  virtual void exitFunctionCallExpr(CalcParser::FunctionCallExprContext * /*ctx*/) override { }

  virtual void enterNumberExpr(CalcParser::NumberExprContext * /*ctx*/) override { }
  virtual void exitNumberExpr(CalcParser::NumberExprContext * /*ctx*/) override { }

  virtual void enterIdExpr(CalcParser::IdExprContext * /*ctx*/) override { }
  virtual void exitIdExpr(CalcParser::IdExprContext * /*ctx*/) override { }

  virtual void enterParenExpr(CalcParser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(CalcParser::ParenExprContext * /*ctx*/) override { }

  virtual void enterFunc(CalcParser::FuncContext * /*ctx*/) override { }
  virtual void exitFunc(CalcParser::FuncContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

