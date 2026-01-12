/**
 * Chapter 5.2: Creating Sparse Matrices
 *
 * Topics: Triplet insertion, coeffRef, makeCompressed
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.2 Creating Sparse Matrices ===\n\n";

    // Method 1: Using triplets (recommended for construction)
    typedef Triplet<double> T;
    vector<T> triplets;

    // Create a simple 5x5 sparse matrix
    int rows = 5, cols = 5;
    triplets.push_back(T(0, 0, 4.0));   // (row, col, value)
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

    cout << "Sparse matrix (tridiagonal):\n" << MatrixXd(A_sparse) << "\n\n";
    cout << "Number of non-zeros: " << A_sparse.nonZeros() << "\n";
    cout << "Total entries: " << A_sparse.rows() * A_sparse.cols() << "\n";
    cout << "Fill ratio: " << 100.0 * A_sparse.nonZeros() / (rows * cols) << "%\n\n";

    // Method 2: Using coeffRef (for incremental updates)
    SparseMatrix<double> B_sparse(3, 3);
    B_sparse.reserve(VectorXi::Constant(3, 2));  // Reserve ~2 entries per column
    B_sparse.coeffRef(0, 0) = 1.0;
    B_sparse.coeffRef(0, 1) = 2.0;
    B_sparse.coeffRef(1, 1) = 3.0;
    B_sparse.coeffRef(2, 2) = 4.0;
    B_sparse.makeCompressed();  // Important: compress after construction

    cout << "Matrix B:\n" << MatrixXd(B_sparse) << "\n";

    return 0;
}
