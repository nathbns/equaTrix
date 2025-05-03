#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <ostream>
#include <complex>
using namespace std;

/**
 * @brief Class representing a matrix of double values
 */


class Matrix {
    private:
        /** @brief 2D vector storing matrix data */
        vector<vector<double> > data;
        /** @brief Number of columns in matrix */
        unsigned int length;
        /** @brief Number of rows in matrix */
        unsigned int height;

    public:

        Matrix();
        /**
         * @brief Construct a new Matrix object
         * @param n Number of rows
         * @param m Number of columns
         */
        Matrix(unsigned int n, unsigned int m);

        /**
         * @brief Construct a new Matrix object from an existing Matrix
         * @param m Another instance of Matrix
         */
        Matrix(const Matrix &m);

        /**
         * @brief Destroy the Matrix object
         */
        ~Matrix();

        /**
         * @brief Fill matrix with values from vector
         * @param d Vector containing values to fill matrix with
         */
        void fillMatrix(vector<double> d);

        /**
         * @brief Get the height (number of rows) of matrix
         * @return unsigned int Number of rows
         */
        unsigned int getHeight() const;

        /**
         * @brief Get the length (number of columns) of matrix
         * @return unsigned int Number of columns
         */
        unsigned int getLength() const;

        /**
         * @brief Get a specific column of the matrix
         * @param i Column index
         * @return vector<double> Column vector
         */
        vector<double> getColumn(unsigned int i) const;

        /**
         * @brief Get a specific row of the matrix
         * @param j Row index
         * @return vector<double> Row vector
         */
        vector<double> getRow(unsigned int i) const;

        void setRow(unsigned int i, vector<double> v);

        /**
         * @brief Calculate transpose of matrix
         * @return Matrix& Transposed matrix
         */
        Matrix transpose() const;

        /**
         * @brief Calculate determinant of matrix
         * @return double Determinant value
         */
        double determinant() const;

        Matrix getId(unsigned int size) const;

        /**
         * @brief Calculate inverse of matrix
         * @return Matrix& Inverse matrix
         */
        Matrix getInverse();

        /**
         * @brief Get basis of kernel (null space) of matrix
         * @return vector<vector<double>> Basis vectors of kernel
         */
        vector<vector<double> > getKerBase() const;

        /**
         * @brief Get basis of image (column space) of matrix
         * @return vector<vector<double>> Basis vectors of image
         */
        vector<vector<double> > getImBase() const;

        unsigned int rank();

        /**
         * @brief Calculate trace of matrix
         * @return double Trace value
         */
        double trace() const;

        /**
         * @brief Calculate power of matrix
         * @return Matrix& Matrix raised to power
         */
        Matrix powMatrix(unsigned int n);

        /**
         * @brief Equality comparison operator
         * @param m Matrix to compare with
         * @return true if matrices are equal
         * @return false if matrices are not equal
         */
        bool operator==(const Matrix &m) const;

        /**
         * @brief Addition operator
         * @param m Matrix to add
         * @return Matrix& Result of addition
         */
        Matrix operator+(const Matrix &m);

        /**
         * @brief Multiplication operator
         * @param m Matrix to multiply with
         * @return Matrix& Result of multiplication
         */
        Matrix operator*(const Matrix &m);

        Matrix operator*(double d);

        /**
         * @brief Subtraction operator
         * @param m Matrix to subtract
         * @return Matrix& Result of subtraction
         */
        Matrix operator-(const Matrix &m);

        /**
         * @brief Inequality comparison operator
         * @param m Matrix to compare with
         * @return true if matrices are not equal
         * @return false if matrices are equal
         */
        bool operator!=(const Matrix &m);

        /**
         * @brief Change value of specific element in matrix
         * @param e New value
         * @param i Row index
         * @param j Column index
         */
        void setElem(double e, unsigned int i, unsigned int j);

        /**
         * @brief Get value of specific element in matrix
         * @param i Row index
         * @param j Column index
         * @return double Element value
         */
        double getElem(unsigned int i, unsigned int j) const;

        /**
        * @brief Calculate the eigenvalues of the matrix
        * @details Uses QR decomposition method to compute the eigenvalues of the matrix.
        *          The eigenvalues are the complex numbers λ that satisfy the equation Ax = λx,
        *          where A is the matrix and x is a non-zero vector.
        * @return vector<complex<double>> Vector containing all eigenvalues of the matrix
        * @note The matrix must be square for this operation to be valid
        * @see qr_decomposition
        */
        vector<complex<double>> eigenvalues();

        /**
        * @brief Calculate the eigenvectors of the matrix
        * @details Computes the eigenvectors associated with each eigenvalue of the matrix.
        *          An eigenvector v of a square matrix A is a non-zero vector that satisfies
        *          the equation Av = λv, where λ is the corresponding eigenvalue.
        *          The function solves the system (A - λI)v = 0 for each eigenvalue λ.
        * @return vector<vector<double>> Matrix where each column is an eigenvector of the matrix
        * @note The matrix must be square for this operation to be valid
        * @see eigenvalues
        */        
        vector<vector<double>> eigenvectors();

        /**
         * @brief Output stream operator
         * @param s Output stream
         * @param m Matrix to output
         * @return ostream& Modified output stream
         */
        friend ostream& operator<<(ostream &s, const Matrix &m);

        /**
         * @brief Test function for the Matrix class
         * @details This function creates matrixes and test the different features
         * @return int exit code (0 if success)
         */
        static int testMatrix();

        /**
         * @brief Perform QR decomposition of the matrix
         * @details Decomposes the matrix into an orthogonal matrix Q and an upper triangular matrix R,
         *          such that A = Q * R where A is the original matrix
         * @param Q Reference to matrix that will store the orthogonal matrix Q
         * @param R Reference to matrix that will store the upper triangular matrix R 
         */
        void qrDecomposition(Matrix& Q, Matrix& R);
};

#endif