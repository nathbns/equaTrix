
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CalcParser.
 */
class  CalcVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CalcParser.
   */
    virtual std::any visitProg(CalcParser::ProgContext *context) = 0;

    virtual std::any visitToTerm(CalcParser::ToTermContext *context) = 0;

    virtual std::any visitAddSubExpr(CalcParser::AddSubExprContext *context) = 0;

    virtual std::any visitMulDivExpr(CalcParser::MulDivExprContext *context) = 0;

    virtual std::any visitToPower(CalcParser::ToPowerContext *context) = 0;

    virtual std::any visitInfixPowExpr(CalcParser::InfixPowExprContext *context) = 0;

    virtual std::any visitToFactor(CalcParser::ToFactorContext *context) = 0;

    virtual std::any visitUnaryMinusExpr(CalcParser::UnaryMinusExprContext *context) = 0;

    virtual std::any visitUnaryPlusExpr(CalcParser::UnaryPlusExprContext *context) = 0;

    virtual std::any visitFunctionCallExpr(CalcParser::FunctionCallExprContext *context) = 0;

    virtual std::any visitNumberExpr(CalcParser::NumberExprContext *context) = 0;

    virtual std::any visitIdExpr(CalcParser::IdExprContext *context) = 0;

    virtual std::any visitParenExpr(CalcParser::ParenExprContext *context) = 0;

    virtual std::any visitFunc(CalcParser::FuncContext *context) = 0;


};

