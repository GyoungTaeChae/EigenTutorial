/**
 * Chapter 5.3: Sparse Matrix Operations
 *
 * Topics: Transpose, addition, multiplication, sparse-vector product
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>

int main() {
    std::cout << "=== 5.3 Sparse Operations ===\n\n";

    // Create a sparse matrix using triplets
    typedef Eigen::Triplet<double> T;
    std::vector<T> triplets;
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

    Eigen::SparseMatrix<double> A_sparse(rows, cols);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    // Basic operations preserve sparsity
    Eigen::SparseMatrix<double> C_sparse = A_sparse.transpose();
    Eigen::SparseMatrix<double> D_sparse = A_sparse + C_sparse;  // Sparse + Sparse = Sparse

    std::cout << "A^T:\n" << Eigen::MatrixXd(C_sparse) << "\n\n";
    std::cout << "A + A^T:\n" << Eigen::MatrixXd(D_sparse) << "\n\n";

    // Sparse matrix-vector product (efficient)
    Eigen::VectorXd x(5);
    x << 1, 2, 3, 4, 5;
    Eigen::VectorXd result = A_sparse * x;
    std::cout << "A * x = " << result.transpose() << "\n";

    return 0;
}
