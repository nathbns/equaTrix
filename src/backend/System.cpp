#include "System.h" 
#include <iostream>  
#include <cmath> 


System::System() : mL(Matrix()), mR(Matrix()) {}


System::System(const Matrix& l, const Matrix& r): mL(l), mR(r) {}


Matrix System::get_mL() const{
    return mL;
}


Matrix System::get_mR() const{
    return mR;  // Fix: return mR instead of mL
}



void System::downScaling() {
    unsigned int n = mL.getHeight();
    unsigned int m = mL.getLength();
    
    // Check that the dimensions are valid
    if (n == 0 || m == 0) {
        return;
    }
    
    
    for (unsigned int i = 0; i < n && i < m; i++) {
        // Null pivot check
        if (std::abs(mL.getElem(i, i)) < 1e-10) {
            // Look for a non-zero pivot in the same column
            bool found = false;
            for (unsigned int k = i + 1; k < n; k++) {
                if (std::abs(mL.getElem(k, i)) > 1e-10) {
                    // Swap lines i and k
                    for (unsigned int j = 0; j < m; j++) {
                        double temp = mL.getElem(i, j);
                        mL.setElem(mL.getElem(k, j), i, j);
                        mL.setElem(temp, k, j);
                    }
                    // Also exchange in the right matrix
                    for (unsigned int j = 0; j < mR.getLength(); j++) {
                        double temp = mR.getElem(i, j);
                        mR.setElem(mR.getElem(k, j), i, j);
                        mR.setElem(temp, k, j);
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                // No non-zero pivot found, move to next column
                continue;
            }
        }
        
        for (unsigned int j = i + 1; j < n; j++) {
            double coeff = mL.getElem(j, i) / mL.getElem(i, i);
            
            for (unsigned int k = 0; k < m; k++) {
                double newValue = mL.getElem(j, k) - coeff * mL.getElem(i, k);
                mL.setElem(newValue, j, k);
            }
            
            // Also apply to the right matrix
            for (unsigned int k = 0; k < mR.getLength(); k++) {
                cout << "" << endl;
                double newRValue = mR.getElem(j, k) - coeff * mR.getElem(i, k);
                mR.setElem(newRValue, j, k);
            }
        }
    }
}


void System::upScaling() {
    unsigned int n = mL.getHeight();
    unsigned int m = mL.getLength();

    // Check that the dimensions are valid
    if (n == 0 || m == 0) {
        return;
    }

    for (int i = std::min(n, m) - 1; i > 0; i--) {
        // Null pivot check
        if (std::abs(mL.getElem(i, i)) < 1e-10) {
            continue;
        }

        for (int j = i - 1; j >= 0; j--) {
            double coeff = mL.getElem(j, i) / mL.getElem(i, i);

            for (unsigned int k = 0; k < m; k++) {
                double newValue = mL.getElem(j, k) - coeff * mL.getElem(i, k);
                mL.setElem(newValue, j, k);
            }
            
            // Also apply to the right matrix
            for (unsigned int k = 0; k < mR.getLength(); k++) {
                double newRValue = mR.getElem(j, k) - coeff * mR.getElem(i, k);
                mR.setElem(newRValue, j, k);
            }
        }
    }
}


void System::reduceLines() {
    for (unsigned int i = 0; i < mL.getHeight(); i++) {
        if (i < mL.getLength() && std::abs(mL.getElem(i, i)) > 1e-10) { 
            double divisor = mL.getElem(i, i);
            
            // Normalize the left matrix row
            for (unsigned int j = 0; j < mL.getLength(); j++) {
                mL.setElem(mL.getElem(i, j) / divisor, i, j);
            }
            
            // Normalize the right matrix row (all columns)
            for (unsigned int j = 0; j < mR.getLength(); j++) {
                mR.setElem(mR.getElem(i, j) / divisor, i, j);
            }
        }
    }
}


std::vector<double> SystemSolver::solveLinearSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants){
    int n = coefficients.size();
    int m = coefficients[0].size();
    
    // Check if the system can have a unique solution
    if (n < m) {
        // No more unknowns than equations - no unique solution
        return std::vector<double>();
    }
    
    // Creation of the augmented matrix
    std::vector<std::vector<double> > augmented(n, std::vector<double>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            augmented[i][j] = coefficients[i][j];
        }
        augmented[i][m] = constants[i];
    }
    
    // Gaussian elimination with partial pivoting
    for (int i = 0; i < m; ++i) {
        // Find the line of maximum pivot (partial pivot)
        int maxRow = i;
        double maxVal = std::abs(augmented[i][i]);
        
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(augmented[k][i]) > maxVal) {
                maxVal = std::abs(augmented[k][i]);
                maxRow = k;
            }
        }
        
        // Swap lines if necessary
        if (maxRow != i) {
            std::swap(augmented[i], augmented[maxRow]);
        }
        
        // Check if the matrix is ​​singular
        if (std::abs(augmented[i][i]) < 1e-10) {
            return std::vector<double>(); // Return an empty vector if no unique solution
        }
        
        // Eliminate below the pivot
        for (int k = i + 1; k < n; ++k) {
            double factor = augmented[k][i] / augmented[i][i];
            for (int j = i; j <= m; ++j) {
                augmented[k][j] -= factor * augmented[i][j];
            }
        }
    }
    
    // Check the consistency of the remaining equations
    for (int i = m; i < n; ++i) {
        bool allZeros = true;
        for (int j = 0; j < m; ++j) {
            if (std::abs(augmented[i][j]) > 1e-10) {
                allZeros = false;
                break;
            }
        }
        // If all coefficients are zero but the constant is not, the system is inconsistent
        if (allZeros && std::abs(augmented[i][m]) > 1e-10) {
            return std::vector<double>(); // No solution
        }
    }
    
    // Backward substitution to find the values ​​of the unknowns
    std::vector<double> solution(m);
    for (int i = m - 1; i >= 0; --i) {
        solution[i] = augmented[i][m];
        for (int j = i + 1; j < m; ++j) {
            solution[i] -= augmented[i][j] * solution[j];
        }
        solution[i] /= augmented[i][i];
    }
    
    return solution;
}


SystemSolver::SystemType SystemSolver::analyzeSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants){
    int n = coefficients.size();
    int m = coefficients[0].size();
    
    // Creation of matrices for calculating the rank
    std::vector<std::vector<double> > coeffMatrix = coefficients;
    
    // Creation of the augmented matrix
    std::vector<std::vector<double> > augmentedMatrix(n, std::vector<double>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            augmentedMatrix[i][j] = coefficients[i][j];
        }
        augmentedMatrix[i][m] = constants[i];
    }
    
    // Reduced echelon formatting of the coefficient matrix
    int rankCoeffs = 0;
    int lead = 0;
    
    for (int r = 0; r < n && lead < m; ++r) {
        int i = r;
        
        // Find a non-zero pivot
        while (i < n && std::abs(coeffMatrix[i][lead]) < 1e-10) {
            ++i;
        }
        
        if (i == n) {
            // No non-zero pivot in this column
            ++lead;
            if (lead < m) {
                --r;
            }
            continue;
        }
        
        // Swap lines if necessary
        if (i != r) {
            std::swap(coeffMatrix[i], coeffMatrix[r]);
        }
        
        // Normalize the pivot line
        double pivot = coeffMatrix[r][lead];
        for (int j = lead; j < m; ++j) {
            coeffMatrix[r][j] /= pivot;
        }
        
        // Remove this variable from other lines
        for (int i = 0; i < n; ++i) {
            if (i != r) {
                double factor = coeffMatrix[i][lead];
                for (int j = lead; j < m; ++j) {
                    coeffMatrix[i][j] -= factor * coeffMatrix[r][j];
                }
            }
        }
        
        ++rankCoeffs;
        ++lead;
    }
    
    // Reduced echelon formatting of the augmented matrix
    int rankAugmented = 0;
    lead = 0;
    
    for (int r = 0; r < n && lead < m + 1; ++r) {
        int i = r;
        
        // Find a non-zero pivot
        while (i < n && std::abs(augmentedMatrix[i][lead]) < 1e-10) {
            ++i;
        }
        
        if (i == n) {
            // No non-zero pivot in this column
            ++lead;
            if (lead < m + 1) {
                --r;
            }
            continue;
        }
        
        // Swap lines if necessary
        if (i != r) {
            std::swap(augmentedMatrix[i], augmentedMatrix[r]);
        }
        
        // Normalize the pivot line
        double pivot = augmentedMatrix[r][lead];
        for (int j = lead; j < m + 1; ++j) {
            augmentedMatrix[r][j] /= pivot;
        }
        
        // Remove this variable from other lines
        for (int i = 0; i < n; ++i) {
            if (i != r) {
                double factor = augmentedMatrix[i][lead];
                for (int j = lead; j < m + 1; ++j) {
                    augmentedMatrix[i][j] -= factor * augmentedMatrix[r][j];
                }
            }
        }
        
        ++rankAugmented;
        ++lead;
    }
    
    // Check if there are any lines that indicate an inconsistency (0 = non-zero constant)
    for (int i = 0; i < n; ++i) {
        bool allZero = true;
        for (int j = 0; j < m; ++j) {
            if (std::abs(augmentedMatrix[i][j]) > 1e-10) {
                allZero = false;
                break;
            }
        }
        
        // If all coefficients are zero but the constant is not, the system has no solution
        if (allZero && std::abs(augmentedMatrix[i][m]) > 1e-10) {
            return SystemType::NoSolution;
        }
    }
    
    // Apply the Rouché-Capelli theorem
    
    // If the rank of the coefficient matrix is ​​different from the rank of the augmented matrix,
    // then the system has no solution
    if (rankCoeffs != rankAugmented) {
        return SystemType::NoSolution;
    }
    
    // If the rank of the coefficient matrix is ​​equal to the number of unknowns,
    // then the system has a unique solution
    if (rankCoeffs == m) {
        return SystemType::Unique;
    }
    
    // If the rank of the coefficient matrix is ​​less than the number of unknowns,
    // and equal to the rank of the augmented matrix, then the system has infinitely many solutions
    return SystemType::InfinitelyManySolutions;
}


SystemSolver::ParametricSolution SystemSolver::solveParametricSystem(const std::vector<std::vector<double> > &coefficients, const std::vector<double> &constants){
    int n = coefficients.size();
    int m = coefficients[0].size();
    
    // Creation of the augmented matrix
    std::vector<std::vector<double> > augmented(n, std::vector<double>(m + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            augmented[i][j] = coefficients[i][j];
        }
        augmented[i][m] = constants[i];
    }
    
    // Gaussian elimination with partial pivoting (reduced echelon form)
    std::vector<int> pivotCols; // Columns having pivot
    
    // Put the matrix in reduced echelon form (REF)
    int lead = 0;
    for (int r = 0; r < n && lead < m; ++r) {
        // Find the maximum pivot in the current column
        int i_max = r;
        double max_val = std::abs(augmented[r][lead]);
        
        for (int i = r + 1; i < n; ++i) {
            if (std::abs(augmented[i][lead]) > max_val) {
                i_max = i;
                max_val = std::abs(augmented[i][lead]);
            }
        }
        
        // If the maximum pivot is zero, move to the next column
        if (max_val < 1e-10) {
            ++lead;
            --r;
            continue;
        }
        
        // Swap the r and i_max lines
        if (i_max != r) {
            std::swap(augmented[r], augmented[i_max]);
        }
        
        // Normalize the pivot line
        double pivot = augmented[r][lead];
        for (int j = lead; j <= m; ++j) {
            augmented[r][j] /= pivot;
        }
        
        // Delete the other lines
        for (int i = 0; i < n; ++i) {
            if (i != r) {
                double factor = augmented[i][lead];
                for (int j = lead; j <= m; ++j) {
                    augmented[i][j] -= factor * augmented[r][j];
                }
            }
        }
        
        // This column contains a pivot
        pivotCols.push_back(lead);
        ++lead;
    }
    
    // Determine the free and dependent variables
    ParametricSolution solution;
    solution.isFreeVariable.resize(m, true);
    
    // Mark pivot (dependent) variables
    for (int col : pivotCols) {
        solution.isFreeVariable[col] = false;
    }
    
    // Calculate the number of free and dependent variables
    int numFreeVars = 0;
    for (int j = 0; j < m; ++j) {
        if (solution.isFreeVariable[j]) {
            ++numFreeVars;
        }
    }
    int numDepVars = m - numFreeVars;
    
    // Initialize the vectors for the parametric solution
    solution.coefficients.resize(numDepVars, std::vector<double>(numFreeVars, 0.0));
    solution.constants.resize(numDepVars, 0.0);
    
    // Express the dependent variables as a function of the free variables
    int depIndex = 0;
    for (int row = 0; row < pivotCols.size(); ++row) {
        int pivotCol = pivotCols[row];
        int freeIndex = 0;
        
        // Constant for this dependent variable
        solution.constants[depIndex] = augmented[row][m];
        
        // Coefficients of free variables
        for (int j = 0; j < m; ++j) {
            if (solution.isFreeVariable[j]) {
                // The variable in column j is free, its coefficient is the opposite of the value in the matrix
                solution.coefficients[depIndex][freeIndex] = -augmented[row][j];
                ++freeIndex;
            }
        }
        
        ++depIndex;
    }
    
    return solution;
}


void System::userSolveSystem() {
    int n, m;
    std::cout << "Entrez le nombre d'équations : ";
    std::cin >> n;
    std::cout << "Entrez le nombre d'inconnues : ";
    std::cin >> m;
    
    std::vector<std::vector<double> > coefficients(n, std::vector<double>(m, 0.0));
    std::vector<double> constants(n, 0.0);
    
    std::cout << "Entrez les coefficients du système et les constantes:" << std::endl;
    std::cout << "Format: Pour chaque équation, entrez d'abord les " << m << " coefficients puis la constante" << std::endl;
    
    for (int i = 0; i < n; ++i) {
        std::cout << "Équation " << (i+1) << " : ";
        for (int j = 0; j < m; ++j) {
            std::cin >> coefficients[i][j];
        }
        std::cin >> constants[i];
    }
    
    // System type analysis
    SystemSolver::SystemType type = SystemSolver::analyzeSystem(coefficients, constants);
    
    switch (type) {
        case SystemSolver::SystemType::Unique : 
            {
                std::vector<double> solution = SystemSolver::solveLinearSystem(coefficients, constants);
                
                // Check if the solution is valid (non-empty)
                if (solution.empty()) {
                    std::cout << "Erreur lors de la résolution du système. La matrice est peut-être singulière." << std::endl;
                } else {
                    std::cout << "Le système a une solution unique :" << std::endl;
                    for (int i = 0; i < m; ++i) {
                        std::cout << "x" << (i+1) << " = " << solution[i] << std::endl;
                    }
                }
            }
            break;
        case SystemSolver::SystemType::InfinitelyManySolutions :
            {
                std::cout << "Le système a une infinité de solutions." << std::endl;
                
                // Get the parametric solution
                SystemSolver::ParametricSolution paramSolution = SystemSolver::solveParametricSystem(coefficients, constants);
                
                // Identify free and dependent variables
                std::vector<int> freeVars;
                std::vector<int> depVars;
                
                for (int i = 0; i < m; ++i) {
                    if (paramSolution.isFreeVariable[i]) {
                        freeVars.push_back(i);
                    } else {
                        depVars.push_back(i);
                    }
                }
                
                // Display free variables
                std::cout << "Variables libres: ";
                for (int var : freeVars) {
                    std::cout << "x" << (var+1) << " ";
                }
                std::cout << std::endl;
                
                // Display the expressions of the dependent variables
                std::cout << "Solution paramétrique:" << std::endl;
                for (int i = 0; i < depVars.size(); ++i) {
                    std::cout << "x" << (depVars[i]+1) << " = " << paramSolution.constants[i];
                    
                    int freeIndex = 0;
                    for (int j = 0; j < freeVars.size(); ++j) {
                        double coeff = paramSolution.coefficients[i][freeIndex];
                        freeIndex++;
                        
                        if (std::abs(coeff) < 1e-10) continue; // Ignore near-zero coefficients
                        
                        if (coeff > 0) {
                            std::cout << " + " << coeff << "*x" << (freeVars[j]+1);
                        } else {
                            std::cout << " - " << std::abs(coeff) << "*x" << (freeVars[j]+1);
                        }
                    }
                    std::cout << std::endl;
                }
            }
            break;
        case SystemSolver::SystemType::NoSolution :
            std::cout << "Le système n'a pas de solution." << std::endl;
            break;
    }
}


