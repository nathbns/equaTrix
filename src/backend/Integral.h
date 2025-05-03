#ifndef _INTEGRAL_H_
#define _INTEGRAL_H_

#include "Function.h"
#include <string>
#include <vector>
#include <memory>

/**
 * @brief Enumeration representing the different integration methods
 */
enum class IntegrationMethod {
    RECTANGLE,
    TRAPEZOID
};

/**
 * @brief Class representing an integral
 */
class Integral {
    private:
        /**
         * @brief Lower bound of the integration
         */
        double lowerBound;
        /**
         * @brief Upper bound of the integration
         */
        double upperBound;
        /**
         * @brief Shared pointer to the function to integrate
         */
        std::shared_ptr<Function> f;
        /**
         * @brief Number of intervals
         */
        unsigned int intervals;
        /**
         * @brief Integration method
         */
        IntegrationMethod method;

    public :
        /**
         * @brief Default constructor
         * @details Initializes an integral with default values: f(x)=0, bounds [0,1], 100 intervals, rectangle method
         */
        Integral();
        /**
         * @brief Parameterized constructor
         * @param expression Function to integrate
         * @param lower Lower bound of integration
         * @param upper Upper bound of integration
         * @param n Number of intervals
         * @param m Integration method
         */
        Integral(const std::string& expression, double lower, double upper, unsigned int n = 100, IntegrationMethod m = IntegrationMethod::RECTANGLE);
        
        /**
         * @brief Evaluates the integral using rectangle method
         * @return Approximate value of the integral
         */
        double evaluateByRectangles() const;
        /**
         * @brief Evaluates the integral using trapezoid method
         * @return Approximate value of the integral
         */
        double evaluateByTrapezoids() const;
        /**
         * @brief Evaluates the integral using the selected method
         * @return Approximate value of the integral
         */
        double evaluate() const; 
        /**
         * @brief Sets the function to integrate
         * @param expression Mathematical expression of the function
         */
        void setFunction(const std::string& expression);
        /**
         * @brief Sets the integration bounds
         * @param lower Lower bound
         * @param upper Upper bound
         */
        void setBounds(double lower, double upper);
        /**
         * @brief Sets the number of intervals
         * @param n Number of intervals
         */
        void setIntervals(unsigned int n);
        /**
         * @brief Sets the integration method
         * @param m Integration method
         */
        void setMethod(IntegrationMethod m);
        
        /**
         * @brief Gets the function expression
         * @return String representation of the function
         */
        std::string getFunctionExpression() const;
        /**
         * @brief Gets the lower bound
         * @return Lower bound value
         */
        double getLowerBound() const;
        /**
         * @brief Gets the upper bound
         * @return Upper bound value
         */
        double getUpperBound() const;
        /**
         * @brief Gets the number of intervals
         * @return Number of intervals
         */
        unsigned int getIntervals() const;
        /**
         * @brief Gets the integration method
         * @return Current integration method
         */
        IntegrationMethod getMethod() const;
        /**
         * @brief Generates explanation text for rectangle method
         * @return Formatted explanation string
         */
        std::string rectangleExplanation() const;
        
        /**
         * @brief Generates explanation text for trapezoid method
         * @return Formatted explanation string
         */
        std::string trapezoidExplanation() const;
        /**
         * @brief Gets explanation for the current integration method
         * @return Formatted explanation string
         */
        std::string getExplanation() const;
        /**
         * @brief Gets points for plotting the function
         * @param numPoints Number of points to generate
         * @return Vector of (x,y) coordinate pairs
         */
        std::vector<std::pair<double, double>> getPlotPoints(unsigned int numPoints = 100) const;
        /**
         * @brief Gets points for visualizing rectangle method
         * @return Vector of (x,y) coordinate pairs representing rectangles
         */
        std::vector<std::pair<double, double>> getRectanglePoints() const;
        /**
         * @brief Gets points for visualizing trapezoid method
         * @return Vector of (x,y) coordinate pairs representing trapezoids
         */
        std::vector<std::pair<double, double>> getTrapezoidPoints() const;
};
#endif