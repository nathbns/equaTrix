
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcVisitor.h"


/**
 * This class provides an empty implementation of CalcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CalcBaseVisitor : public CalcVisitor {
public:

  virtual std::any visitProg(CalcParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitToTerm(CalcParser::ToTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExpr(CalcParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivExpr(CalcParser::MulDivExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitToPower(CalcParser::ToPowerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInfixPowExpr(CalcParser::InfixPowExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitToFactor(CalcParser::ToFactorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryMinusExpr(CalcParser::UnaryMinusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryPlusExpr(CalcParser::UnaryPlusExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCallExpr(CalcParser::FunctionCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberExpr(CalcParser::NumberExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpr(CalcParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(CalcParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc(CalcParser::FuncContext *ctx) override {
    return visitChildren(ctx);
  }


};

