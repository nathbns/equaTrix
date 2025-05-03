#pragma once
#include <utility>

enum TypeNode {
    ADD, SUB, MUL, DIV, SQRT, SIN, COS, ARCCOS, ARCSIN, ARCTAN, TAN, LN, EXP, LOG, CST, VAR, POW
};

struct ExprNode {
    ExprNode * left;
    ExprNode * right;
    TypeNode type;
    double val;
};

ExprNode * ExprNodeOpBin(TypeNode type, ExprNode * l, ExprNode * r);
ExprNode * ExprNodeCst(double v);
ExprNode * ExprNodeVar();
ExprNode * ExprNodeFct(TypeNode type, ExprNode * r);
void deleteExprTreeNode(ExprNode * n);
ExprNode* cloneExprNode(const ExprNode* node);

class ExprTree {
public:
    ExprNode * root;
    double evaluate(double x);
    std::pair<double, double> evalDiff(double x);
    
    ExprTree();
    explicit ExprTree(ExprNode * node);

    ExprTree(const ExprTree& other); 
    ExprTree& operator=(const ExprTree& other); 

    ~ExprTree();
    static void TestExprTree();
};

