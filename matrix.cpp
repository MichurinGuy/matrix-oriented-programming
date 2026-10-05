#include "matrix.h"


int kron(int x, int y);     // kroneker delta
int kron(int x, int y) {
    if (x == y) { return 1; }
    else { return 0; }
}


Matrix::Matrix(int N) {
    size = N;
    elem = new double[N*N];
    for (int row = 0; row < N; row++) {
        for (int col = 0; col<N; col++) {
            elem[N*row + col] = 0;
        }
    }
}
Matrix::Matrix(const Matrix& a) {
    size = a.ord();
    elem = new double[size*size];
    for (int i = 0; i < size*size; i++) { elem[i] = a[i]; }
}
Matrix& Matrix::operator=(const Matrix& B) {
    delete[] elem;
    size = B.ord();
    elem = new double[size * size];
    for (int i = 0; i < size * size; i++) {
        elem[i] = B[i];
    }
    return *this;
}
Matrix::~Matrix() { delete[] elem; }

int Matrix::ord() const { return size; }
double Matrix::operator[](const int index) const { return elem[index]; }
double& Matrix::operator[](const int index) { return elem[index]; }
double Matrix::operator()(const int row, const int col) const { return elem[size * row + col]; }
double& Matrix::operator()(const int row, const int col) { return elem[size * row + col]; }

Matrix Matrix::operator+(const Matrix& B) {
        if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
        Matrix A(size);
        for (int i = 0; i < size*size; i++) {
            A[i] = (*this)[i] + B[i];
        }
        return A;
}
Matrix& Matrix::operator+=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
    for (int i = 0; i < size*size; i++) {
        (*this)[i] += B[i];
    }
    return *this;
}
Matrix Matrix::operator-(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(size);
    for (int i = 0; i <size*size; i++) {
        A[i] = (*this)[i] - B[i];
    }
    return A;
}
Matrix& Matrix::operator-=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
    for (int i = 0; i < size*size; i++) {
        (*this)[i] -= B[i];
    }
    return *this;
}
Matrix Matrix::operator*(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            double val = 0;
            for (int i = 0; i < size; i++) {
                val += (*this)(row, i) * B(i, col);
            }
            A(row, col) = val;
        }
    }
    return A;
}
Matrix& Matrix::operator*=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return *this; }
    double* arr = new double[size * size];
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            double val = 0;
            for (int i = 0; i < size; i++) {
                val += (*this)(row, i) * B(i, col);
            }
            arr[size * row + col] = val;
        }
    }
    for (int i = 0; i < size * size; i++) {
        (*this)[i] = arr[i];
    }
    delete[] arr;
    return *this;
}
Matrix Matrix::operator*(const double n) {
    Matrix A(size);
    for (int i = 0; i < size * size; i++) {
        A[i] = n * (*this)[i];
    }
    return A;
}
Matrix& Matrix::operator*=(const double n) {
    for (int i = 0; i < size * size; i++) {
        (*this)[i] *= n;
    }
    return *this;
}

    
bool Matrix::operator<(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] >= B[i]) { return false; }
    }
    return true;
}
bool Matrix::operator>(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] <= B[i]) { return false; }
    }
    return true;
}
bool Matrix::operator<=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] > B[i]) { return false; }
    }
    return true;
}
bool Matrix::operator>=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] < B[i]) { return false; }
    }
    return true;
}
bool Matrix::operator==(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] != B[i]) { return false; }
    }
    return true;
}
bool Matrix::operator!=(const Matrix& B) {
    if (size != B.ord()) { std::cout << "size incompatible" << std::endl; return false; }
    for (int i = 0; i<size*size; i++) {
        if ((*this)[i] != B[i]) { return true; }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Matrix& A) {
    int s = A.ord();
    for (int row = 0; row < s; row++) {
        for (int col = 0; col < s; col++) {
            out << A(row, col);
            if (col != s - 1) { out << " "; }
        }
        out << std::endl;
    }
    return out;
}

Matrix Matrix::trans() {
    Matrix A(size);
    for (int row = 0; row < size; row++) {
        for (int col = row; col < size; col++) {
            A(row, col) = (*this)(col, row);
            if (row != col) { A(col, row) = (*this)(row, col); }
        }
    }
    return A;
}
double* Matrix::act(const double* vec) const {
    double* res = new double[size];
    for (int row = 0; row < size; row++) {
        res[row] = 0;
        for (int col = 0; col < size; col++) {
            res[row] += ((*this)(row, col)) * vec[col];
        }
    }
    return res;
}

Matrix Matrix::row_swap(const int a, const int b) const {
    if ((a >= size) || (b >= size)) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(a, i) = (*this)(b, i);
        A(b, i) = (*this)(a, i);
    }
    return A;
}
Matrix Matrix::row_add(const int a, const int b, const double coef) const {
    if ((a >= size) || (b >= size)) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(a, i) += ((*this)(b, i))*coef;
    }
    return A;
}
Matrix Matrix::row_mult(const int a, const double coef) const {
    if (a >= size) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(a, i) *= coef;
    }
    return A;
}
Matrix Matrix::col_swap(const int a, const int b) const {
    if ((a >= size) || (b >= size)) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(i, a) = (*this)(i, b);
        A(i, b) = (*this)(i, a);
    }
    return A;
}
Matrix Matrix::col_add(const int a, const int b, const double coef) const {
    if ((a >= size) || (b >= size)) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(i, a) += ((*this)(i, b)) * coef;
    }
    return A;
}
Matrix Matrix::col_mult(const int a, const double coef) const {
    if (a >= size) { std::cout << "size incompatible" << std::endl; return *this; }
    Matrix A(*this);
    for (int i = 0; i < size; i++) {
        A(i, a) *= coef;
    }
    return A;
}

Matrix Matrix::ech() const {
    Matrix A(*this);
    for (int N = 0; N < size - 1; N++) {
        int row = N;
        while ((A(row, N) == 0)&&(row<size)) { row++; }
        if (row == size) { continue; }
        A = A.row_swap(N, row);
        for (int r = N + 1; r < size; r++) {
            if (A(r, N) != 0) { A = A.row_add(r, N, -A(r, N) / A(N, N)); }
        }
    }
    return A;
}
Matrix Matrix::impech() const {
    Matrix A((*this).ech());
    int col = 0;
    for (int row = 0; row < size; row++) {
        while ((A(row, col) == 0) && (col < size)) { col++; }
        if (col == size) { return A; }
        A = A.row_mult(row, 1 / A(row, col));
        for (int r = 0; r < row; r++) {
            A = A.row_add(r, row, -A(r, col));
        }
    }
    return A;
}
double Matrix::det() const {
    Matrix A(*this);
    double ans = 1;
    for (int N = 0; N < size - 1; N++) {        // exact copy of A.ech() but keeping track of sign changes during row swaps
        int row = N;
        while ((A(row, N) == 0) && (row < size)) { row++; }
        if (row == size) { continue; }
        A = A.row_swap(N, row);
        if (N != row) { ans *= -1; }
        for (int r = N + 1; r < size; r++) {
            if (A(r, N) != 0) { A = A.row_add(r, N, -A(r, N) / A(N, N)); }
        }
    }
    for (int n = 0; n < size; n++) {
        ans *= A(n, n);
    }
    return ans;
}
double Matrix::tr() const {
    double a = 0;
    for (int i = 0; i < size; i++) {
        a += (*this)(i, i);
    }
    return a;
}
int Matrix::rk() const {
    Matrix A((*this).ech());
    int rank = 0;
    int col = 0;
    int row = 0;
    while (row < size) {
        while (((*this)(row, col) == 0) && (col < size)) { col++; }
        if (col != size) { rank++; row++; }
        else { return rank; }
    }
    return rank;
}
Matrix Matrix::inv() const {
    Matrix A(*this), E(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            E(i, j) = kron(i, j);
        }
    }
    for (int N = 0; N < size - 1; N++) {        // A.impech() but copying the elementary operations on an identity matrix
        int row = N;
        while ((A(row, N) == 0) && (row < size)) { row++; }
        if (row == size) { continue; }
        A = A.row_swap(N, row);
        E = E.row_swap(N, row);
        for (int r = N + 1; r < size; r++) {
            if (A(r, N) != 0) {
                double c = -A(r, N) / A(N, N);
                A = A.row_add(r, N, c);
                E = E.row_add(r, N, c);
            }
        }
    }
    int col = 0;
    for (int row = 0; row < size; row++) {
        while ((A(row, col) == 0) && (col < size)) { col++; }
        if (col == size) { std::cout << "not invertible" << std::endl; return Matrix(size); }
        double c = 1 / A(row, col);
        A = A.row_mult(row, c);
        E = E.row_mult(row, c);
        for (int r = 0; r < row; r++) {
            c = -A(r, col);
            A = A.row_add(r, row, c);
            E = E.row_add(r, row, c);
        }
    }
    return E;
}