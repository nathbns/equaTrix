#ifndef _SYSTEM_H_  
#define _SYSTEM_H_

#include <map>
#include <vector>
#include <cmath>
#include "Matrix.h"

/**
 * @class System
 * @brief Represents a mathematical system with left and right matrices.
 * 
 * This class implements a mathematical system that can be manipulated
 * and solved. It contains operations for scaling, switching, finding
 * coefficients, and solving systems of equations.
 */
class System {
    private:
        /// @brief The left matrix of the system
        Matrix mL;
        /// @brief The right matrix of the system
        Matrix mR;

    public:
        /**
         * @brief Construct a new System with specified left and right matrices
         * @param l The left matrix
         * @param r The right matrix
         */
        System(const Matrix& l, const Matrix& r);
        
        /**
         * @brief Default constructor
         */
        System();
        
        /**
         * @brief Get the left matrix
         * @return A reference to the left matrix
         */
        Matrix get_mL() const;
        
        /**
         * @brief Get the right matrix
         * @return A reference to the right matrix
         */
        Matrix get_mR() const;

        /**
         * @brief Scales the matrix downward (Gaussian method)
         * ​​@details Transforms the matrix to have zeros below the diagonal
         */
        void downScaling();


        /**
         * @brief Scales the matrix upwards (Gauss-Jordan method)
         * ​​@details Transforms the matrix to have 1s on the diagonal and 0s elsewhere
         */
        void upScaling();

        /**
         * @brief Normalizes the matrix rows to have 1s on the diagonal
         * @details Divides each row by the corresponding diagonal element
         */
        void reduceLines();
        
        /**
         * @brief Solves a system of linear equations entered by the user
         * @details Asks the user to enter the coefficients and constants of the system,
         * then solves the system and displays the solution
         */
        static void userSolveSystem();
};

/**
 * @class SystemSolver
 * @brief Utility for solving systems of linear equations
 *
 * This class provides methods for solving systems of linear equations
 * and analyzing their solution types.
 */
class SystemSolver {
public:
    /**
     * @brief Types of systems of equations
     */
    enum SystemType {
        Unique,                 ///< Unique solution
        InfinitelyManySolutions, ///< Infinite number of solutions
        NoSolution              ///< No solution
    };

    /**
     * @brief Structure representing a parametric solution
     */
    struct ParametricSolution {
        std::vector<bool> isFreeVariable;        ///< Indicates whether a variable is free (true) or dependent (false)
        std::vector<std::vector<double> > coefficients; ///< Coefficients of free variables in the expression of dependent variables
        std::vector<double> constants;           ///< Constant terms in the expression of dependent variables
    };

    /**
     * @brief Solve a system of linear equations
     * @param coefficients Coefficient matrix
     * @param constants Vector of constants
     * @return A vector containing the solution, empty if there is no unique solution
     */
    static std::vector<double> solveLinearSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants);
    
    /**
     * @brief Analyze the type of system of equations
     * @param coefficients Coefficient matrix
     * @param constants Constant vector
     * @return The type of system (unique, infinitely many solutions, no solution)
     */
    static SystemType analyzeSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants);
    
    /**
     * @brief Obtain the parametric solution of a system with free variables
     * @param coefficients Coefficient matrix
     * @param constants Constant vector
     * @return Structure containing the parametric solution
     */
    static ParametricSolution solveParametricSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants);
};

#endif