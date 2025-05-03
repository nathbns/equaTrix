#include "Function.h"
#include <iostream>
#include "antlr4-runtime.h"
#include "../antlr4/CalcLexer.h"
#include "../antlr4/CalcParser.h"
#include <cmath>
#include <cassert>

Function::Function(const std::string &expression) : expr(expression), tree(nullptr) {
    setTree(expr);
}

Function::~Function() {
    if (tree.root) {
        deleteExprTreeNode(tree.root);
        tree.root = nullptr; 
    }
}

std::string Function::getExpression() const {
    return expr;
}

double Function::evaluate(double x) {
    return tree.evaluate(x); 
}

std::pair<double, double> Function::automaticDifferentiation(double x) {
    return tree.evalDiff(x); 
}

void Function::setTree(const std::string &expr) {
    antlr4::ANTLRInputStream input(expr);
    CalcLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    CalcParser parser(&tokens);
    CalcParser::ProgContext* parseTree = parser.prog();

    CalcEvalVisitor visitor;
    auto result = visitor.visit(parseTree);
    if (!result.has_value())
        throw std::runtime_error("Parsing failed: no value produced.");

    ExprNode* root = nullptr;
    try {
        root = std::any_cast<ExprNode*>(result);
    } catch (const std::bad_any_cast& e) {
        throw std::runtime_error(std::string("Failed to cast ExprNode*: ") + e.what());
    }

    if (!root)
        throw std::runtime_error("ExprNode creation failed (null pointer).");

    
    this->tree = ExprTree(root);
}


std::vector<double> Function::getRoots() const {
    std::vector<double> roots;
    const int MAX_ITERATIONS = 100;
    const double EPSILON = 1e-10;         // For convergence
    const double UNIQUE_EPSILON = 1e-5;   // For root uniqueness
    const double STEP = 0.1;              // Step size for initial guesses
    
    // Use a sign change approach combined with Newton-Raphson
    for (double x0 = -10.0; x0 < 10.0; x0 += STEP) {
        double f0 = const_cast<Function*>(this)->evaluate(x0);
        double f1 = const_cast<Function*>(this)->evaluate(x0 + STEP);
        
        // Check for sign change (potential root between x0 and x0+STEP)
        if (f0 * f1 <= 0.0 || std::abs(f0) < EPSILON || std::abs(f1) < EPSILON) {
            // Start Newton-Raphson from this promising interval
            double x = (std::abs(f0) < std::abs(f1)) ? x0 : x0 + STEP;
            bool converged = false;
            int iterations = 0;
            
            // Save original x for fallback
            double original_x = x;
            
            // Newton-Raphson iteration
            while (iterations < MAX_ITERATIONS) {
                auto [fx, fpx] = const_cast<Function*>(this)->automaticDifferentiation(x);
                
                if (std::abs(fx) < EPSILON) {
                    converged = true;
                    break;
                }
                
                if (std::abs(fpx) < EPSILON) {
                    // If derivative is too small, use bisection fallback
                    x = (x0 + (x0 + STEP)) / 2.0;
                    f0 = const_cast<Function*>(this)->evaluate(x);
                    if (std::abs(f0) < EPSILON) {
                        converged = true;
                        break;
                    }
                    iterations++;
                    continue;
                }
                
                double x_new = x - fx / fpx;
                
                // Check if we're converging
                if (std::abs(x_new - x) < EPSILON) {
                    x = x_new;
                    converged = true;
                    break;
                }
                
                // Check if we're getting out of the search range
                if (x_new < -15.0 || x_new > 15.0) {
                    // Try bisection as fallback
                    x = (x0 + (x0 + STEP)) / 2.0;
                } else {
                    x = x_new;
                }
                
                iterations++;
            }
            
            // If Newton-Raphson didn't converge, try bisection method
            if (!converged) {
                double a = x0;
                double b = x0 + STEP;
                double c;
                double fa = const_cast<Function*>(this)->evaluate(a);
                double fb = const_cast<Function*>(this)->evaluate(b);
                
                for (int i = 0; i < 50; i++) {
                    c = (a + b) / 2.0;
                    double fc = const_cast<Function*>(this)->evaluate(c);
                    
                    if (std::abs(fc) < EPSILON) {
                        x = c;
                        converged = true;
                        break;
                    }
                    
                    if (fa * fc < 0) {
                        b = c;
                        fb = fc;
                    } else {
                        a = c;
                        fa = fc;
                    }
                }
            }
            
            if (converged) {
                // Refine the root to ensure high accuracy
                for (int i = 0; i < 2; i++) {
                    auto [fx, fpx] = const_cast<Function*>(this)->automaticDifferentiation(x);
                    if (std::abs(fpx) > EPSILON) {
                        x = x - fx / fpx;
                    }
                }
                
                // Check uniqueness
                bool isUnique = true;
                for (const double& root : roots) {
                    if (std::abs(root - x) < UNIQUE_EPSILON) {
                        isUnique = false;
                        break;
                    }
                }
                
                if (isUnique && std::abs(x) <= 10.1) {  // Stay within search range
                    roots.push_back(x);
                }
            }
        }
    }
    
    std::sort(roots.begin(), roots.end());
    return roots;
}

void Function::testFunction() {
    // Test 1: Polynomial functions
    {
        Function f("x^2");
        assert(std::abs(f.evaluate(4) - 16.0) < 1e-10);
        auto [val, der] = f.automaticDifferentiation(4);
        assert(std::abs(val - 16.0) < 1e-10);
        assert(std::abs(der - 8.0) < 1e-10);
    }
    
    // Test 2: Trigonometric functions
    {
        Function f("sin(x)");
        assert(std::abs(f.evaluate(0) - 0.0) < 1e-10);
        auto [val, der] = f.automaticDifferentiation(0);
        assert(std::abs(val - 0.0) < 1e-10);
        assert(std::abs(der - 1.0) < 1e-10);
    }
    
    // Test 3: Exponential and logarithmic
    {
        Function f("exp(x)");
        assert(std::abs(f.evaluate(0) - 1.0) < 1e-10);
        auto [val, der] = f.automaticDifferentiation(0);
        assert(std::abs(val - 1.0) < 1e-10);
        assert(std::abs(der - 1.0) < 1e-10);
    }
    
    // Test 4: Complex expressions
    {
        Function f("sin(x^2) + cos(x)/exp(x)");
        double x = 1.0;
        auto [val, der] = f.automaticDifferentiation(x);
        assert(!std::isnan(val) && !std::isnan(der));
    }
    
    // Test 5: Square root
    {
        Function f("sqrt(x)");
        assert(std::abs(f.evaluate(4) - 2.0) < 1e-10);
        auto [val, der] = f.automaticDifferentiation(4);
        assert(std::abs(val - 2.0) < 1e-10);
        assert(std::abs(der - 0.25) < 1e-10);
    }
    
    // Test 6: Inverse trigonometric
    {
        Function f("arcsin(x)");
        assert(std::abs(f.evaluate(0) - 0.0) < 1e-10);
        auto [val, der] = f.automaticDifferentiation(0);
        assert(std::abs(val - 0.0) < 1e-10);
        assert(std::abs(der - 1.0) < 1e-10);
    }
    
    // Test 7: Multiple operations
    {
        Function f("2*x^3 + 3*x^2 + 4*x + 5");
        double x = 2.0;
        auto [val, der] = f.automaticDifferentiation(x);
        assert(std::abs(val - (16 + 12 + 8 + 5)) < 1e-10);
        assert(std::abs(der - (24 + 12 + 4)) < 1e-10);
    }
    
    // Test 8: Division
    {
        Function f("1/x");
        double x = 2.0;
        auto [val, der] = f.automaticDifferentiation(x);
        assert(std::abs(val - 0.5) < 1e-10);
        assert(std::abs(der + 0.25) < 1e-10);
    }
    
    // Test 9: Logarithmic functions
    {
        Function f("ln(x)");
        double x = 1.0;
        auto [val, der] = f.automaticDifferentiation(x);
        assert(std::abs(val - 0.0) < 1e-10);
        assert(std::abs(der - 1.0) < 1e-10);
    }
    
    // Test 10: Combined functions
    {
        Function f("sin(x)*exp(x) + ln(x+1)");
        double x = 0.0;
        auto [val, der] = f.automaticDifferentiation(x);
        assert(std::abs(val - 0.0) < 1e-10);
        assert(!std::isnan(der));
    }
    // Test 11: Roots
    {
        Function f("x^2 - 4");
        std::vector<double> roots = f.getRoots();
        assert(roots.size() == 2);
        assert(std::abs(roots[0] + 2.0) < 1e-10);
        assert(std::abs(roots[1] - 2.0) < 1e-10);
    }
    // Test 12: No roots
    {
        Function f("x^2 + 1");
        std::vector<double> roots = f.getRoots();
        assert(roots.empty());
    }

    std::cout << "All function tests passed successfully!" << std::endl;
}
