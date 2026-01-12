/**
 * Chapter 5.3: Sparse Matrix Operations
 *
 * Topics: Transpose, addition, multiplication, sparse-vector product
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.3 Sparse Operations ===\n\n";

    // Create a sparse matrix using triplets
    typedef Triplet<double> T;
    vector<T> triplets;
    int rows = 5, cols = 5;

    triplets.push_back(T(0, 0, 4.0));
    triplets.push_back(T(0, 1, -1.0));
    triplets.push_back(T(1, 0, -1.0));
    triplets.push_back(T(1, 1, 4.0));
    triplets.push_back(T(1, 2, -1.0));
    triplets.push_back(T(2, 1, -1.0));
    triplets.push_back(T(2, 2, 4.0));
    triplets.push_back(T(2, 3, -1.0));
    triplets.push_back(T(3, 2, -1.0));
    triplets.push_back(T(3, 3, 4.0));
    triplets.push_back(T(3, 4, -1.0));
    triplets.push_back(T(4, 3, -1.0));
    triplets.push_back(T(4, 4, 4.0));

    SparseMatrix<double> A_sparse(rows, cols);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    // Basic operations preserve sparsity
    SparseMatrix<double> C_sparse = A_sparse.transpose();
    SparseMatrix<double> D_sparse = A_sparse + C_sparse;  // Sparse + Sparse = Sparse

    cout << "A^T:\n" << MatrixXd(C_sparse) << "\n\n";
    cout << "A + A^T:\n" << MatrixXd(D_sparse) << "\n\n";

    // Sparse matrix-vector product (efficient)
    VectorXd x(5);
    x << 1, 2, 3, 4, 5;
    VectorXd result = A_sparse * x;
    cout << "A * x = " << result.transpose() << "\n";

    return 0;
}
