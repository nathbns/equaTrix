#include <iostream>
#include "ExprTree.h"
#include <cmath>

ExprNode * ExprNodeOpBin(TypeNode type, ExprNode * l, ExprNode * r) {
    ExprNode * n = new ExprNode;
    n->type = type;
    n->left = l;
    n->right = r;
    n->val = 0.0 / 0.0;
    return n;
}

ExprNode * ExprNodeCst(double v) {
    ExprNode * n = new ExprNode;
    n->type = CST;
    n->left = nullptr;
    n->right = nullptr;
    n->val = v;
    return n;
}

ExprNode * ExprNodeVar() {
    ExprNode * n = new ExprNode;
    n->type = VAR;
    n->left = nullptr;
    n->right = nullptr;
    n->val = 0.0 / 0.0;
    return n;
}

ExprNode * ExprNodeFct(TypeNode type, ExprNode * r) {
    ExprNode * n = new ExprNode;
    n->type = type;
    n->left = nullptr;
    n->right = r;
    n->val = 0.0 / 0.0;
    return n;
}

void deleteExprTreeNode(ExprNode * n) {
    if (n != nullptr) {
        switch (n->type) {
            case VAR:
            case CST:
                delete n;
                break;
            case ADD:
            case SUB:
            case MUL:
            case DIV:
                deleteExprTreeNode(n->left);
                deleteExprTreeNode(n->right);
                delete n;
                break;
            case SQRT:
            case LOG:
            case EXP:
            case SIN:
            case COS:
            case TAN:
            case ARCSIN:
            case ARCCOS:
            case ARCTAN:
            case LN:
                deleteExprTreeNode(n->right);
                delete n;
                break;
            case POW:
                deleteExprTreeNode(n->left);
                deleteExprTreeNode(n->right);
                delete n;
                break;
            default:
                std::cerr << "Unexpected node type during deletion." << std::endl;
        }
    }
}

double evaluateAux(ExprNode * node, double x) {
    double vl, vr;
    switch(node->type) {
        case ADD :
            vl = evaluateAux(node->left, x);
            vr = evaluateAux(node->right, x);
            return vl + vr;
        case SUB :
            vl = evaluateAux(node->left, x);
            vr = evaluateAux(node->right, x);
            return vl - vr;
        case MUL :
            vl = evaluateAux(node->left, x);
            vr = evaluateAux(node->right, x);
            return vl * vr;
        case DIV :
            vl = evaluateAux(node->left, x);
            vr = evaluateAux(node->right, x);
            return vl / vr;
        case SQRT :
            vr = evaluateAux(node->right, x);
            return sqrt(vr);
        case EXP :
            vr = evaluateAux(node->right, x);
            return exp(vr);
        case LOG :
            vr = evaluateAux(node->right, x);
            return log(vr);
        case SIN :
            vr = evaluateAux(node->right, x);
            return sin(vr);
        case COS :
            vr = evaluateAux(node->right, x);
            return cos(vr);
        case TAN :
            vr = evaluateAux(node->right, x);
            return tan(vr);
        case ARCSIN :
            vr = evaluateAux(node->right, x);
            return asin(vr);
        case ARCCOS :
            vr = evaluateAux(node->right, x);
            return acos(vr);
        case ARCTAN :
            vr = evaluateAux(node->right, x);
            return atan(vr);
        case POW :
            vl = evaluateAux(node->left, x);
            vr = evaluateAux(node->right, x);
            return pow(vl, vr);
        case LN :
            vr = evaluateAux(node->right, x);
            return log(vr);
        case CST :
            return node->val;
        case VAR :
            return x;

        default : std::cout<< "should not happen" << std::endl;
    }
}

double ExprTree::evaluate(double x) {
    return evaluateAux(root, x);
}

ExprTree::ExprTree() : root(nullptr) {}

ExprTree::ExprTree(ExprNode * node) : root(node) {}

ExprTree::ExprTree(const ExprTree& other) {
    root = cloneExprNode(other.root);
}

ExprTree& ExprTree::operator=(const ExprTree& other) {
    if (this != &other) {
        deleteExprTreeNode(root);
        root = cloneExprNode(other.root);
    }
    return *this;
}

ExprTree::~ExprTree() {
    deleteExprTreeNode(root);
    root = nullptr;
}

std::pair<double, double> evalDiffAux(ExprNode* node, double x) {
    if (node == nullptr) {
        return {0.0, 0.0};
    }

    switch (node->type) {
        case CST:
            return {node->val, 0.0}; 
            
        case VAR:
            return {x, 1.0}; 
            
        case ADD: {
            auto [v1, d1] = evalDiffAux(node->left, x);
            auto [v2, d2] = evalDiffAux(node->right, x);
            return {v1 + v2, d1 + d2}; 
        }
            
        case SUB: {
            auto [v1, d1] = evalDiffAux(node->left, x);
            auto [v2, d2] = evalDiffAux(node->right, x);
            return {v1 - v2, d1 - d2}; 
        }
            
        case MUL: {
            auto [v1, d1] = evalDiffAux(node->left, x);
            auto [v2, d2] = evalDiffAux(node->right, x);
            return {v1 * v2, d1 * v2 + v1 * d2}; 
        }
            
        case DIV: {
            auto [v1, d1] = evalDiffAux(node->left, x);
            auto [v2, d2] = evalDiffAux(node->right, x);
            return {v1 / v2, (d1 * v2 - v1 * d2) / (v2 * v2)}; 
        }
            
        case SQRT: {
            auto [v, d] = evalDiffAux(node->right, x);
            double sqrtV = std::sqrt(v);
            return {sqrtV, d / (2.0 * sqrtV)};
        }
            
        case EXP: {
            auto [v, d] = evalDiffAux(node->right, x);
            double expV = std::exp(v);
            return {expV, expV * d}; 
        }
            
        case LOG: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::log(v), d / v}; 
        }
        case SIN: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::sin(v), std::cos(v) * d}; 
        }
        case COS: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::cos(v), -std::sin(v) * d}; 
        }
        case TAN: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::tan(v), (1.0 / std::cos(v) / std::cos(v)) * d}; 
        }
        case ARCSIN: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::asin(v), d / std::sqrt(1 - v * v)}; 
        }
        case ARCCOS: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::acos(v), -d / std::sqrt(1 - v * v)}; 
        }
        case ARCTAN: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::atan(v), d / (1 + v * v)}; 
        }
        case LN: {
            auto [v, d] = evalDiffAux(node->right, x);
            return {std::log(v), d / v}; 
        }
        case POW: {
            auto [v1, d1] = evalDiffAux(node->left, x);
            auto [v2, d2] = evalDiffAux(node->right, x);
            return {std::pow(v1, v2), std::pow(v1, v2) * (d2 * std::log(v1) + v2 * d1 / v1)}; 
        }   
        default:
            return {0.0, 0.0};
    }
}

std::pair<double, double> ExprTree::evalDiff(double x) {
    return evalDiffAux(root, x);
}
ExprNode* cloneExprNode(const ExprNode* node) {
    if (!node) return nullptr;

    ExprNode* copy = new ExprNode;
    copy->type = node->type;
    copy->val = node->val;
    copy->left = cloneExprNode(node->left);
    copy->right = cloneExprNode(node->right);
    return copy;
}


void ExprTree::TestExprTree() {
    // example expression: sqrt((3 + x) * x)
    ExprNode* n1 = ExprNodeCst(3.0);
    ExprNode* n2 = ExprNodeVar();
    ExprNode* n3 = ExprNodeOpBin(ADD, n1, n2);
    ExprNode* n4 = ExprNodeOpBin(MUL, n3, n2);
    ExprNode* n5 = ExprNodeFct(SQRT, n4);
    ExprTree tree(n5);
    
    double x = 4.0;
    std::cout << "Expression: " << tree.evaluate(x) << std::endl;
    auto [value, derivative] = tree.evalDiff(x);
    std::cout << "Value at x=" << x << ": " << value << ", Derivative at x=" << x << ": " << derivative << std::endl;
}