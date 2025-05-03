#include "Matrix.h"
#include "System.h"
#include <iostream>
#include <ostream>
#include <cassert>
#include <numeric>
#include <complex>
#include <set>
using namespace std;


Matrix::Matrix() {
    length = 0;
    height = 0;
}

Matrix::Matrix(unsigned int n, unsigned int m){
    height = n;
    length = m;
    data.resize(n, vector<double>(m, 0.0));
}

Matrix::Matrix(const Matrix &m){
    length = m.getLength();
    height = m.getHeight();
    data = m.data;
}

Matrix::~Matrix(){}

void Matrix::fillMatrix(vector<double> d){
    int line = 0;
    for (unsigned int i = 0; i < d.size(); i++){
        if (i > 0 && i % getLength() == 0) line++;
        data[line][i % getLength()] = d[i];
    }
}


unsigned int Matrix::getHeight() const{
    return height;
}

unsigned int Matrix::getLength() const{
    return length;
}


vector<double> Matrix::getColumn(unsigned int j) const{
    vector<double> res;
    for (unsigned int i = 0; i< data.size(); i++){
        res.push_back(data[i][j]);
    }
    return res;
}

vector<double> Matrix::getRow(unsigned int i) const{
    return data[i];
}

void Matrix::setRow(unsigned int i, vector<double> v){
    data[i] = v;
}

Matrix Matrix::transpose() const{
    Matrix m(getHeight(), getLength());
    for (unsigned int i = 0; i < m.getHeight(); i++){
        m.setRow(i, getColumn(i));
    }
    return m;
}

double Matrix::determinant() const {
    if (getHeight() != getLength()) {
        throw std::runtime_error("Le déterminant est défini uniquement pour les matrices carrées.");
    }

    unsigned int n = getHeight();
    if (n == 1) {
        return getElem(0, 0);
    }
    if (n == 2) {
        return getElem(0, 0) * getElem(1, 1) - getElem(0, 1) * getElem(1, 0);
    }

    System s(*this, this->getId(n)); // Creation of the system with identity
    s.downScaling(); // Gaussian reduction
    Matrix res = s.get_mL(); // Lower echelon matrix
    
    double det = 1.0;
    for (unsigned int i = 0; i < n; i++) {
        det *= res.getElem(i, i); // Product of diagonal elements
    }
    
    return det;
}

vector<vector<double> > Matrix::getKerBase() const {
    unsigned int n = getLength();  // Number of columns
    unsigned int m = getHeight();  // Number of lines
    
    // Create a copy of the matrix so as not to modify the original
    Matrix m_cp = *this;
    
    // Apply Gaussian reduction
    vector<double> v (m,0);
    Matrix zero(m,0);
    System gauss(m_cp, zero);
    gauss.downScaling();

    // Identify the pivot columns
    vector<bool> is_pivot(n, false);
    vector<int> pivot_row(m, -1);

    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            if (gauss.get_mL().getElem(i, j) != 0) {
                is_pivot[j] = true;
                pivot_row[i] = j;
                break;
            }
        }
    }

    // Identify free variables
    vector<int> free_vars;
    for (unsigned int j = 0; j < n; ++j) {
        if (!is_pivot[j]) {
            free_vars.push_back(j);
        }
    }


    // Build the core base
    vector<vector<double> > kernel_basis;
    for (int free_var : free_vars) {
        vector<double> basis_vector(n, 0.0);
        basis_vector[free_var] = 1.0;

        // Express in terms of pivots
        for (unsigned int i = 0; i < m; ++i) {
            int pivot = pivot_row[i];
            if (pivot != -1 && gauss.get_mL().getElem(i, pivot) != 0) {
                basis_vector[pivot] = -gauss.get_mL().getElem(i, free_var) / gauss.get_mL().getElem(i, pivot);
            }
        }

        kernel_basis.push_back(basis_vector);
    }
    return kernel_basis;
}



vector<vector<double>> Matrix::getImBase() const {
    unsigned int h = getHeight();
    unsigned int l = getLength();
    Matrix m = *this;
    Matrix mR(h, 1);
    mR.fillMatrix(vector<double>(h, 0));
    System s(m, mR);
    s.downScaling();
    m = s.get_mL();

    vector<unsigned int> pivot_columns;

    for (unsigned int i = 0; i < h; i++) {
        for (unsigned int j = 0; j < l; j++) {
            if (abs(m.getElem(i, j)) > 1e-12) { // Pivot found (avoids numerical errors)
                pivot_columns.push_back(j);
                break; // One pivot per line
            }
        }
    }

    vector<vector<double>> res;
    for (unsigned int idx : pivot_columns) {
        res.push_back(getColumn(idx)); // We take the columns of the original matrix
    }

    return res;
}


Matrix Matrix::getId(unsigned int size) const{
    assert(size<=5);
    Matrix res(size, size);
    for (unsigned int i = 0; i < size; i++){
        for (unsigned int j = 0; j < size; j++){
            if (i == j) res.setElem(1, i, j);
            else res.setElem(0, i, j);
        }
    }
    return res;
}

Matrix Matrix::getInverse() {
    assert(getHeight() == getLength());
    System s(*this, getId(getHeight()));
    s.downScaling();
    s.downScaling();
    s.reduceLines();
    return s.get_mR();
}

unsigned int Matrix::rank(){
    return getImBase().size();
}

double Matrix::trace() const{
    assert(getHeight() == getLength());
    double res = 0;
    for (unsigned int i = 0; i < getHeight(); i++){
        res += getElem(i, i);
    }
    return res;
}

Matrix Matrix::powMatrix(unsigned int n){
    assert(getHeight() == getLength());
    if (n==0) return getId(getHeight());
    Matrix res = *this;
    for (unsigned int i = 0; i < n-1; i++){
        res = res * *this;
    }
    return res;
}

bool Matrix::operator==(const Matrix &m) const{
    if (getHeight() != m.getHeight() || getLength() != m.getLength()) return false;
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int j = 0; j < getLength(); j++){
            if (getElem(i, j) != m.getElem(i, j)) return false;
        }
    }
    return true;
}

Matrix Matrix::operator+(const Matrix &m){
    assert(getLength() == m.getLength() && getHeight() == m.getHeight());
    Matrix res(getHeight(), getLength());
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int j = 0; j < getLength(); j++){
            res.setElem(getElem(i, j) + m.getElem(i, j), i, j);
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &m){
    assert(getLength() == m.getHeight());
    Matrix res(getHeight(), m.getLength());
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int k = 0; k < m.getLength(); k++){
            double r = 0;
            for (unsigned int j = 0; j < getLength(); j++){
                r += getElem(i, j) * m.getElem(j, k);
            }
            res.setElem(r, i, k);
        }
    }
    return res;
}

Matrix Matrix::operator*(double d){
    Matrix res(getHeight(), getLength());
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int j = 0; j < getLength(); j++){
            res.setElem(getElem(i, j)*d, i, j);
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &m){
    assert(getLength() == m.getLength() && getHeight() == m.getHeight());
    Matrix res(getHeight(), getLength());
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int j = 0; j < getLength(); j++){
            res.setElem(getElem(i, j) - m.getElem(i, j), i, j);
        }
    }
    return res;
}

bool Matrix::operator!=(const Matrix &m){
    if (getHeight() != m.getHeight() || getLength() != m.getLength()) return true;
    for (unsigned int i = 0; i < getHeight(); i++){
        for (unsigned int j = 0; j < getLength(); j++){
            if (getElem(i, j) != m.getElem(i, j)) return true;
        }
    }
    return false;
}

void Matrix::setElem(double e, unsigned int i, unsigned int j){
    data[i][j] = e;
}

double Matrix::getElem(unsigned int i, unsigned int j) const {
    return data[i][j];
}


ostream& operator<<(ostream &s, const Matrix &m){
    for (unsigned int i = 0; i < m.getHeight(); i++){
        for (unsigned int j = 0; j < m.getLength(); j++){
            s << m.getElem(i, j) << " ";
        }
        s << endl;
    }
    return s;
}



// QR decomposition by the Gram-Schmidt method
void Matrix::qrDecomposition(Matrix &Q, Matrix &R) {
    if (getHeight() != getLength()) {
        throw runtime_error("La matrice doit être carrée pour la décomposition QR.");
    }
    
    int n = getHeight();
    Q = Matrix(n, n);
    R = Matrix(n, n);
    vector<vector<double>> q_vectors(n, vector<double>(n, 0.0));
    
    // Gram-Schmidt algorithm
    for (int j = 0; j < n; j++) {
        vector<double> v = getColumn(j);
        for (int i = 0; i < j; i++) {
            double dot_product = 0.0;
            for (int k = 0; k < n; k++) {
                dot_product += getElem(k, j) * q_vectors[i][k];
            }
            R.data[i][j] = dot_product;
            for (int k = 0; k < n; k++) {
                v[k] -= dot_product * q_vectors[i][k];
            }
        }
        double norm = sqrt(std::inner_product(v.begin(), v.end(), v.begin(), 0.0));
        if (norm > 1e-10) { // Avoid division by zero
            R.data[j][j] = norm;
            for (int k = 0; k < n; k++) {
                q_vectors[j][k] = v[k] / norm;
                Q.data[k][j] = q_vectors[j][k];
            }
        } else {
            R.data[j][j] = 0.0;
            for (int k = 0; k < n; k++) {
                q_vectors[j][k] = 0.0;
                Q.data[k][j] = 0.0;
            }
        }
    }
}

// Implementation of the QR algorithm to calculate all eigenvalues
vector<complex<double>> Matrix::eigenvalues() {
    if (getHeight() != getLength()) {
        throw runtime_error("La matrice doit être carrée pour calculer le spectre.");
    }

    int n = getHeight();
    Matrix A = *this;
    Matrix Q, R;
    const int maxIter = 100;
    const double tol = 1e-10;

    // Iterative QR algorithm
    for (int iter = 0; iter < maxIter; iter++) {
        A.qrDecomposition(Q, R);
        A = R * Q;

        // Convergence: subdiagonal elimination
        bool converge = true;
        for (int i = 0; i < n - 1; i++) {
            if (abs(A.getElem(i + 1, i)) > tol) {
                converge = false;
                break;
            }
        }
        if (converge) break;
    }

    // Spectrum extraction
    vector<complex<double>> vps;
    int i = 0;
    while (i < n) {
        if (i < n - 1 && abs(A.getElem(i + 1, i)) > tol) {
            // 2x2 block to diagonalize
            double a = A.getElem(i, i);
            double b = A.getElem(i, i + 1);
            double c = A.getElem(i + 1, i);
            double d = A.getElem(i + 1, i + 1);
            double trace = a + d;
            double det = a * d - b * c;
            complex<double> trace_c(trace);
            complex<double> det_c(det);
            complex<double> delta = trace_c * trace_c - complex<double>(4.0) * det_c;
            complex<double> sqrt_delta = sqrt(delta);
            complex<double> lambda1 = (trace_c + sqrt_delta) / complex<double>(2.0);
            complex<double> lambda2 = (trace_c - sqrt_delta) / complex<double>(2.0);

            vps.push_back(lambda1);
            vps.push_back(lambda2);
            i += 2;
        } else {
            // Real eigenvalue on the diagonal
            vps.push_back(A.getElem(i, i));
            i++;
        }
    }

    return vps;
}


vector<vector<double>> Matrix::eigenvectors() {
    vector<complex<double>> eigenvalues = this->eigenvalues();
    vector<vector<double>> eigenvectors;
    vector<double> processedEigenvalues;

    for (const auto& lambda : eigenvalues) {
        if (abs(lambda.imag()) > 1e-10) {
            continue;
        }
        
        double realEigenvalue = lambda.real();
        
        bool alreadyProcessed = false;
        for (const auto& processed : processedEigenvalues) {
            if (abs(processed - realEigenvalue) < 1e-10) {
                alreadyProcessed = true;
                break;
            }
        }
        
        if (alreadyProcessed) {
            continue;
        }
        
        processedEigenvalues.push_back(realEigenvalue);
        
        vector<vector<double>> coeffMatrix(this->height, vector<double>(this->length));
        for (unsigned int i = 0; i < this->height; i++) {
            for (unsigned int j = 0; j < this->length; j++) {
                double value = this->getElem(i, j);
                if (i == j) {
                    value -= realEigenvalue;
                }
                coeffMatrix[i][j] = value;
            }
        }

        vector<double> constants(this->height, 0.0);

        SystemSolver::ParametricSolution solution = 
            SystemSolver::solveParametricSystem(coeffMatrix, constants);
        
        for (unsigned int i = 0; i < solution.isFreeVariable.size(); i++) {
            if (solution.isFreeVariable[i]) {
                vector<double> eigenvector(this->length, 0.0);
                
                for (unsigned int j = 0; j < solution.isFreeVariable.size(); j++) {
                    if (solution.isFreeVariable[j]) {
                        eigenvector[j] = (j == i) ? 1.0 : 0.0;
                    }
                }
                
                for (unsigned int j = 0; j < solution.isFreeVariable.size(); j++) {
                    if (!solution.isFreeVariable[j]) {
                        unsigned int pos = 0;
                        for (unsigned int k = 0; k < j; k++) {
                            if (!solution.isFreeVariable[k]) {
                                pos++;
                            }
                        }
                        
                        eigenvector[j] = solution.constants[pos];
                        
                        unsigned int freeIdx = 0;
                        for (unsigned int k = 0; k < solution.isFreeVariable.size(); k++) {
                            if (solution.isFreeVariable[k]) {
                                eigenvector[j] += solution.coefficients[pos][freeIdx] * eigenvector[k];
                                freeIdx++;
                            }
                        }
                    }
                }
                
                double maxAbsVal = 0.0;
                for (const auto& val : eigenvector) {
                    if (abs(val) > maxAbsVal) {
                        maxAbsVal = abs(val);
                    }
                }
                
                if (maxAbsVal > 1e-10) {
                    // Simplify the vector by dividing by the maximum value in absolute value
                    for (auto& val : eigenvector) {
                        val /= maxAbsVal;
                        
                        // Round values ​​very close to zero to zero
                        if (abs(val) < 1e-10) {
                            val = 0.0;
                        }
                    }
                    
                    bool isIndependent = true;
                    for (const auto& existing : eigenvectors) {
                        // Check if the vectors are collinear
                        bool isColinear = true;
                        double ratio = 0.0;
                        bool ratioSet = false;
                        
                        for (unsigned int k = 0; k < eigenvector.size(); k++) {
                            if (abs(eigenvector[k]) > 1e-10 && abs(existing[k]) > 1e-10) {
                                if (!ratioSet) {
                                    ratio = eigenvector[k] / existing[k];
                                    ratioSet = true;
                                } else if (abs(eigenvector[k] / existing[k] - ratio) > 1e-10) {
                                    isColinear = false;
                                    break;
                                }
                            } else if ((abs(eigenvector[k]) > 1e-10) != (abs(existing[k]) > 1e-10)) {
                                isColinear = false;
                                break;
                            }
                        }
                        
                        if (isColinear) {
                            isIndependent = false;
                            break;
                        }
                    }
                    
                    if (isIndependent) {
                        eigenvectors.push_back(eigenvector);
                    }
                }
            }
        }
    }
    
    return eigenvectors;
}

int Matrix::testMatrix(void){
    // Filling
    Matrix m(3,3);
    vector<double> v;
    v.push_back(2); v.push_back(1); v.push_back(1);
    v.push_back(1); v.push_back(1); v.push_back(1); 
    v.push_back(1); v.push_back(2); v.push_back(1);
    m.fillMatrix(v);
    
    // Display and inverse
    cout << endl << "Matrice m créée. Valeurs: " << endl << m << "Inverse: " << endl << m.getInverse();
    
    // Height and width
    cout << endl << "Hauteur : " << m.getHeight() << endl << "Largeur : " << m.getLength() << endl;

    // Getter of columns and rows
    cout << endl << "Première ligne de la matrice : " << endl;
    vector<double> r0 = m.getRow(0);
    for (unsigned int i = 0; i < r0.size(); i++) cout << r0[i] << " ";
    cout << endl << "Colonne du milieu de la matrice : " << endl;
    vector<double> c1 = m.getColumn(1);
    for (unsigned int i = 0; i < c1.size(); i++) cout << c1[i] << " ";
    cout << endl << endl;

    // Transpose
    cout << "Transposée de la matrice : " << endl << m.transpose() << endl;

    // Identity
    cout << "Matrice identité de taille 3 : " << endl << m.getId(3) << endl;

    // Trace
    cout << "Trace de la matrice : " << m.trace() << endl;

    // Determinant
    cout << "Déterminant de la matrice : " << m.determinant() << endl;

    // Equality and difference
    Matrix m2 = m;
    cout << "Doit afficher 1 1 : " << endl;
    bool tmp = m2 == m;
    cout << tmp << " ";
    tmp = m2 != m2.getId(3);
    cout << tmp << " " << endl << endl;

    // Arithmetic operators
    Matrix id3 = m.getId(3);
    cout << "Matrices opérandes : " << endl << m << endl << id3 << endl;
    cout << "Résultat addition : " << endl << m+id3 << endl;
    cout << "Résultat soustraction : " << endl << m-id3 << endl;
    cout << "Résultat multiplication de la première matrice par elle-même : " << endl << m*m << endl;
    cout << "Première matrice puissance 3 : " << endl << m.powMatrix(3);
    

    Matrix m3(3,3);
    vector<double> v1;
    v1.push_back(1); v1.push_back(2); v1.push_back(3);
    v1.push_back(4); v1.push_back(5); v1.push_back(6); 
    v1.push_back(7); v1.push_back(8); v1.push_back(9);
    m3.fillMatrix(v1);

    cout << "Nouvelle matrice : " << endl << m3 << endl << "Base de son image : " << endl;
    vector<vector<double> > v2 = m3.getImBase();
    for (unsigned int i = 0; i < v2.size(); i++){
        cout << "( ";
        for (unsigned int j = 0; j < v2[i].size(); j++){
            cout << v2[i][j] << " ";
        }
        cout << ")" << endl;
    }

    cout << "Nouvelle matrice : " << endl;
    Matrix m4(3,3);
    vector<double> vm4;
    vm4.push_back(1); vm4.push_back(2); vm4.push_back(3);
    vm4.push_back(2); vm4.push_back(4); vm4.push_back(6);
    vm4.push_back(0); vm4.push_back(0); vm4.push_back(0);
    m4.fillMatrix(vm4);
    cout << m4;

    cout << endl << "Base de son noyau : " << endl;
    vector<vector<double> > v3 = m4.getKerBase();
    for (unsigned int i = 0; i < v3.size(); i++){
        cout << "( ";
        for (unsigned int j = 0; j < v3[i].size(); j++){
            cout << v3[i][j] << " ";
        }
        cout << ")" << endl;
    }
    cout << endl;

    cout << "Nouvelle matrice : " << endl;
    Matrix m5(2,2);
    vector<double> vm5;
    vm5.push_back(0); vm5.push_back(-1);
    vm5.push_back(1); vm5.push_back(0);
    m5.fillMatrix(vm5);
    cout << m5;

    vector<complex<double>> sRes = m5.eigenvalues();
    
    cout << "Valeurs propres de la matrice : " << endl;
    for (unsigned int i = 0; i < sRes.size(); i++){
        cout << "( ";
        cout << sRes[i].real() << " ";
        if (sRes[i].imag() != 0){
            if (sRes[i].imag() < 0) {
                cout << "- " << -sRes[i].imag() << " i ";
            }
            else {
                cout << "+ " << sRes[i].imag() << " i ";
            }
        }
        cout << ")" << endl;
    }
    cout << endl;

    Matrix m6(4,4);
    vector<double> vm6;
    vm6.push_back(0); vm6.push_back(1); vm6.push_back(2); vm6.push_back(3);
    vm6.push_back(1); vm6.push_back(0); vm6.push_back(4); vm6.push_back(5);
    vm6.push_back(2); vm6.push_back(4); vm6.push_back(0); vm6.push_back(6);
    vm6.push_back(3); vm6.push_back(5); vm6.push_back(6); vm6.push_back(0);
    m6.fillMatrix(vm6);
    m6.determinant();

    return 0;
}
