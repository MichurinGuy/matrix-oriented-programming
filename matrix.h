#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int size;
    double* elem;
public:
    Matrix(int N = 1);
    Matrix(const Matrix& a);
    Matrix& operator=(const Matrix& B);
    ~Matrix();

    int ord() const;
    double operator[](const int index) const;
    double& operator[](const int index);
    double operator()(const int row, const int col) const;      // rows and columns indexed from 0
    double& operator()(const int row, const int col);

    Matrix operator+(const Matrix& B);
    Matrix& operator+=(const Matrix& B);
    Matrix operator-(const Matrix& B);
    Matrix& operator-=(const Matrix& B);
    Matrix operator*(const Matrix& B);
    Matrix& operator*=(const Matrix& B);
    Matrix operator*(const double n);
    Matrix& operator*=(const double n);

    bool operator<(const Matrix& B);
    bool operator>(const Matrix& B);
    bool operator<=(const Matrix& B);
    bool operator>=(const Matrix& B);
    bool operator==(const Matrix& B);
    bool operator!=(const Matrix& B);

    friend std::ostream& operator<<(std::ostream& out, const Matrix& A);

    Matrix trans();
    double* act(const double* vec) const;
    Matrix row_swap(const int a, const int b) const;        // rows and columns indexed from 0
    Matrix row_add(const int a, const int b, const double coef) const;      // add row b to row a with coefficient coef
    Matrix row_mult(const int a, const double coef) const;
    Matrix col_swap(const int a, const int b) const;
    Matrix col_add(const int a, const int b, const double coef) const;      // add column b to column a with coefficient coef
    Matrix col_mult(const int a, const double coef) const;
    Matrix ech() const;     // turns a metrix into row echelon form
    Matrix impech() const;      // improved row echelon form
    double det() const;
    double tr() const;      // trace
    int rk() const;     // rank
    Matrix inv() const;
};

#endif
