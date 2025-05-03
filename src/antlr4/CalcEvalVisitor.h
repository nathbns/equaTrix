#ifndef CALCEVALVISITOR_H
#define CALCEVALVISITOR_H

#include "CalcBaseVisitor.h"
#include "CalcParser.h"
#include "ExprTree.h"
#include <stdexcept>
#include <string>
#include <any>

class CalcEvalVisitor : public CalcBaseVisitor {
public:
    // prog: expr EOF
    std::any visitProg(CalcParser::ProgContext *ctx) override {
        return visit(ctx->expr());
    }

    // expr: expr op=('+'|'-') term    # AddSubExpr
    std::any visitAddSubExpr(CalcParser::AddSubExprContext *ctx) override {
        ExprNode* left  = std::any_cast<ExprNode*>(visit(ctx->expr()));
        ExprNode* right = std::any_cast<ExprNode*>(visit(ctx->term()));
        return ctx->op->getText() == "+"
             ? ExprNodeOpBin(ADD, left, right)
             : ExprNodeOpBin(SUB, left, right);
    }

    // expr: term                     # ToTerm
    std::any visitToTerm(CalcParser::ToTermContext *ctx) override {
        return visit(ctx->term());
    }

    // term: term op=('*'|'/') power   # MulDivExpr
    std::any visitMulDivExpr(CalcParser::MulDivExprContext *ctx) override {
        ExprNode* left  = std::any_cast<ExprNode*>(visit(ctx->term()));
        ExprNode* right = std::any_cast<ExprNode*>(visit(ctx->power()));
        return ctx->op->getText() == "*"
             ? ExprNodeOpBin(MUL, left, right)
             : ExprNodeOpBin(DIV, left, right);
    }

    // term: power                    # ToPower
    std::any visitToPower(CalcParser::ToPowerContext *ctx) override {
        return visit(ctx->power());
    }

    // power: power '^' factor        # InfixPowExpr
    std::any visitInfixPowExpr(CalcParser::InfixPowExprContext *ctx) override {
        ExprNode* base     = std::any_cast<ExprNode*>(visit(ctx->power()));
        ExprNode* exponent = std::any_cast<ExprNode*>(visit(ctx->factor()));
        return ExprNodeOpBin(POW, base, exponent);
    }

    // power: factor                  # ToFactor
    std::any visitToFactor(CalcParser::ToFactorContext *ctx) override {
        return visit(ctx->factor());
    }

    // factor: '-' factor            # UnaryMinusExpr
    std::any visitUnaryMinusExpr(CalcParser::UnaryMinusExprContext *ctx) override {
        ExprNode* operand = std::any_cast<ExprNode*>(visit(ctx->factor()));
        return ExprNodeOpBin(MUL, ExprNodeCst(-1.0), operand);
    }

    // factor: '+' factor            # UnaryPlusExpr
    std::any visitUnaryPlusExpr(CalcParser::UnaryPlusExprContext *ctx) override {
        return visit(ctx->factor());
    }

    // factor: func '(' expr ')'     # FunctionCallExpr
    std::any visitFunctionCallExpr(CalcParser::FunctionCallExprContext *ctx) override {
        ExprNode* arg = std::any_cast<ExprNode*>(visit(ctx->expr()));
        std::string fn = ctx->func()->getText();
        if      (fn == "sin")    return ExprNodeFct(SIN,    arg);
        else if (fn == "cos")    return ExprNodeFct(COS,    arg);
        else if (fn == "tan")    return ExprNodeFct(TAN,    arg);
        else if (fn == "arcsin") return ExprNodeFct(ARCSIN,arg);
        else if (fn == "arccos") return ExprNodeFct(ARCCOS,arg);
        else if (fn == "arctan") return ExprNodeFct(ARCTAN,arg);
        else if (fn == "ln")     return ExprNodeFct(LN,     arg);
        else if (fn == "log")    return ExprNodeFct(LOG,    arg);
        else if (fn == "exp")    return ExprNodeFct(EXP,    arg);
        else if (fn == "sqrt")   return ExprNodeFct(SQRT,   arg);
        else throw std::runtime_error("Unsupported function: " + fn);
    }

    // factor: NUMBER                # NumberExpr
    std::any visitNumberExpr(CalcParser::NumberExprContext *ctx) override {
        return ExprNodeCst(std::stod(ctx->NUMBER()->getText()));
    }

    // factor: IDX                   # IdExpr
    std::any visitIdExpr(CalcParser::IdExprContext *ctx) override {
        return ExprNodeVar();
    }

    // factor: '(' expr ')'          # ParenExpr
    std::any visitParenExpr(CalcParser::ParenExprContext *ctx) override {
        return visit(ctx->expr());
    }
};

#endif // CALCEVALVISITOR_H