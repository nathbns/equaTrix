#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include "../antlr4/ExprTree.h"
#include "../antlr4/CalcEvalVisitor.h"

/**
 * @class Function
 * @brief Represents a mathematical function and provides methods for evaluation, differentiation, and root finding.
 */
class Function {
    public:
    /**
     * @brief Constructs a Function object with the given mathematical expression.
     * @param expression The mathematical expression as a string.
     */
    Function(const std::string &expression);
    
    /**
     * @brief Destructor for the Function class.
     */
    ~Function();

    /**
     * @brief Evaluates the function for a given value of x.
     * @param x The value at which to evaluate the function. Default is 0.0.
     * @return The result of the function evaluation.
     */
    double evaluate(double x = 0.0); 

    /**
     * @brief Tests the functionality of the Function class.
     * This is a static method used for debugging and validation purposes.
     */
    static void testFunction();

    /**
     * @brief Sets the expression tree for the function based on the given mathematical expression.
     * @param expr The mathematical expression as a string.
     */
    void setTree(const std::string &expr);

    /**
     * @brief Performs automatic differentiation to compute the value of the function and its derivative at a given point.
     * @param x The point at which to compute the function and its derivative. Default is 0.0.
     * @return A pair containing the value of the function and its derivative at the given point.
     */
    std::pair<double,double> automaticDifferentiation(double x = 0.0);

    /**
     * @brief Retrieves the mathematical expression of the function.
     * @return The mathematical expression as a string.
     */
    std::string getExpression() const;

    /**
     * @brief Finds the roots of the function.
     * @return A vector containing the roots of the function.
     */
    std::vector<double> getRoots() const;

private:
    std::string expr;
    ExprTree tree;
};

#endif // FUNCTION_H