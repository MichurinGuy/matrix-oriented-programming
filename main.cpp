#include "matrix.cpp"

int main() {
    int s = 5;
    double* v = new double[s];
    Matrix A(s), B(s), C(s);
    A(0, 0) = 1; A(0, 1) = 0; A(0, 2) = 4; A(0, 3) = 2; A(0, 4) = 5;
    A(1, 0) = 0; A(1, 1) = 0; A(1, 2) = 4; A(1, 3) = 1; A(1, 4) = 10;
    A(2, 0) = 2; A(2, 1) = 3; A(2, 2) = 0; A(2, 3) = 2; A(2, 4) = 0;
    A(3, 0) = 2; A(3, 1) = 1; A(3, 2) = 0; A(3, 3) = 0; A(3, 4) = 3;
    A(4, 0) = 1; A(4, 1) = 2; A(4, 2) = 0; A(4, 3) = 3; A(4, 4) = 1;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            B(i, j) = kron(i, j);
            C(i, j) = 1;
        }
        v[i] = i;
    }
    std::cout << "A:" << std::endl << A << "B:" << std::endl << B << "C:" << std::endl << C;
    std::cout << "A+B:" << std::endl << A + B << "A-B:" << std::endl << A - B << "A*B:" << std::endl << A + B;
    C -= B;
    std::cout << "C-=B:" << std::endl << C << "C*A" << std::endl << C * A;
    std::cout << "v:";
    for (int i = 0; i < s; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl << "action of C on v:";
    v = C.act(v);
    for (int i = 0; i < s; i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl << "A transposed:" << std::endl << A.trans();
    std::cout << "A with row 1 added to 2 with coefficient 1.5:" << std::endl << A.row_add(1, 0, 1.5);
    std::cout << "A with rows 1 and 2 swapped:" << std::endl << A.row_swap(0, 1);
    std::cout << "A with row 2 multiplied by 2:" << std::endl << A.row_mult(1, 2);
    std::cout << "Row echelon form of A:" << std::endl << A.ech() << "det(A):" << std::endl << A.det() << std::endl;
    std::cout << "A^(-1) (*det(A) for readability):" << std::endl << A.inv()*A.det();
    std::cout << "A^(-1)*A:" << std::endl << A.inv() * A << "A*A^(-1):" << std::endl << A * A.inv();

    return 0;
}
