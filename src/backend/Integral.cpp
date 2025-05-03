#include "Integral.h"
#include <cmath>
#include <sstream>
#include <iomanip> 

Integral::Integral() : lowerBound(0.0), upperBound(1.0), intervals(100), method(IntegrationMethod::RECTANGLE) {
    f = std::make_shared<Function>("0");
}

Integral::Integral(const std::string& expression, double lower, double upper, unsigned int n, IntegrationMethod m)
    : lowerBound(lower), upperBound(upper), intervals(n), method(m) {
    f = std::make_shared<Function>(expression);
}

double Integral::evaluateByRectangles() const {
    if (lowerBound >= upperBound) return 0.0;
    
    double h = (upperBound - lowerBound) / intervals;
    double sum = 0.0;
    
    for (unsigned int i = 0; i < intervals; i++) {
        double x = lowerBound + i * h + h / 2; 
        sum += f->evaluate(x);
    }
    
    return sum * h;
}

double Integral::evaluateByTrapezoids() const {
    if (lowerBound >= upperBound) return 0.0;
    
    double h = (upperBound - lowerBound) / intervals;
    double sum = 0.0;
    
    double fa = f->evaluate(lowerBound);
    
    for (unsigned int i = 1; i < intervals; i++) {
        double x = lowerBound + i * h;
        sum += 2 * f->evaluate(x);
    }
    
    double fb = f->evaluate(upperBound);
    
    return (fa + sum + fb) * h / 2.0;
}

double Integral::evaluate() const {
    switch (method) {
        case IntegrationMethod::RECTANGLE:
            return evaluateByRectangles();
        case IntegrationMethod::TRAPEZOID:
            return evaluateByTrapezoids();
        default:
            return evaluateByRectangles();
    }
}

void Integral::setFunction(const std::string& expression) {
    f = std::make_shared<Function>(expression);
}

void Integral::setBounds(double lower, double upper) {
    lowerBound = lower;
    upperBound = upper;
}

void Integral::setIntervals(unsigned int n) {
    intervals = n;
}

void Integral::setMethod(IntegrationMethod m) {
    method = m;
}

std::string Integral::getFunctionExpression() const {
    return f->getExpression();
}

double Integral::getLowerBound() const {
    return lowerBound;
}

double Integral::getUpperBound() const {
    return upperBound;
}

unsigned int Integral::getIntervals() const {
    return intervals;
}

IntegrationMethod Integral::getMethod() const {
    return method;
}

std::string Integral::rectangleExplanation() const {
    std::ostringstream explanation;
    double h = (upperBound - lowerBound) / intervals;
    
    explanation << "Méthode des rectangles avec " << intervals << " intervalles:\n\n";
    explanation << "∫[" << lowerBound << "," << upperBound << "] " << f->getExpression() << " dx ≈ ";
    
    explanation << "h × (";
    for (unsigned int i = 0; i < std::min(intervals, 3u); i++) {
        double x = lowerBound + i * h + h / 2;
        explanation << "f(" << std::fixed << std::setprecision(4) << x << ")";
        if (i < std::min(intervals, 3u) - 1) explanation << " + ";
    }
    
    if (intervals > 3) explanation << " + ... ";
    
    explanation << ") = " << std::fixed << std::setprecision(6) << evaluateByRectangles();
    
    return explanation.str();
}

std::string Integral::trapezoidExplanation() const {
    std::ostringstream explanation;
    double h = (upperBound - lowerBound) / intervals;
    
    explanation << "Méthode des trapèzes avec " << intervals << " intervalles:\n\n";
    explanation << "∫[" << lowerBound << "," << upperBound << "] " << f->getExpression() << " dx ≈ ";
    
    explanation << "h/2 × [f(" << std::fixed << std::setprecision(4) << lowerBound << ")";
    
    // Show some intermediate points
    for (unsigned int i = 1; i < std::min(intervals, 3u); i++) {
        double x = lowerBound + i * h;
        explanation << " + 2×f(" << std::fixed << std::setprecision(4) << x << ")";
    }
    
    if (intervals > 3) explanation << " + ... ";
    
    explanation << " + f(" << std::fixed << std::setprecision(4) << upperBound << ")";
    explanation << "] = " << std::fixed << std::setprecision(6) << evaluateByTrapezoids();
    
    return explanation.str();
}

std::string Integral::getExplanation() const {
    switch (method) {
        case IntegrationMethod::RECTANGLE:
            return rectangleExplanation();
        case IntegrationMethod::TRAPEZOID:
            return trapezoidExplanation();
        default:
            return rectangleExplanation();
    }
}

std::vector<std::pair<double, double>> Integral::getPlotPoints(unsigned int numPoints) const {
    std::vector<std::pair<double, double>> points;
    points.reserve(numPoints);
    
    double step = (upperBound - lowerBound) / (numPoints - 1);
    for (unsigned int i = 0; i < numPoints; i++) {
        double x = lowerBound + i * step;
        try {
            double y = f->evaluate(x);
            if (std::isfinite(y)) {
                points.push_back(std::make_pair(x, y));
            }
        } catch (...) {

        }
    }
    
    return points;
}

std::vector<std::pair<double, double>> Integral::getRectanglePoints() const {
    std::vector<std::pair<double, double>> points;
    double h = (upperBound - lowerBound) / intervals;
    
    for (unsigned int i = 0; i < intervals; i++) {
        double x_left = lowerBound + i * h;
        double x_mid = x_left + h / 2;
        double x_right = x_left + h;
        double y_mid = f->evaluate(x_mid);
        
        points.push_back(std::make_pair(x_left, 0));
        points.push_back(std::make_pair(x_left, y_mid));
        points.push_back(std::make_pair(x_right, y_mid));
        points.push_back(std::make_pair(x_right, 0));
        points.push_back(std::make_pair(x_left, 0)); 
    }
    
    return points;
}

std::vector<std::pair<double, double>> Integral::getTrapezoidPoints() const {
    std::vector<std::pair<double, double>> points;
    double h = (upperBound - lowerBound) / intervals;
    
    for (unsigned int i = 0; i < intervals; i++) {
        double x_left = lowerBound + i * h;
        double x_right = x_left + h;
        double y_left = f->evaluate(x_left);
        double y_right = f->evaluate(x_right);
        
        points.push_back(std::make_pair(x_left, 0));
        points.push_back(std::make_pair(x_left, y_left));
        points.push_back(std::make_pair(x_right, y_right));
        points.push_back(std::make_pair(x_right, 0));
        points.push_back(std::make_pair(x_left, 0)); 
    }
    
    return points;
}