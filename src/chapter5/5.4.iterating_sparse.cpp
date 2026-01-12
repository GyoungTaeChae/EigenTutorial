/**
 * Chapter 5.4: Iterating Over Sparse Matrices
 *
 * Topics: InnerIterator for accessing non-zero elements
 */

#include <iostream>
#include <vector>
#include <Eigen/Sparse>

int main() {
    std::cout << "=== 5.4 Iterating Over Sparse Elements ===\n\n";

    // Create a sparse matrix
    typedef Eigen::Triplet<double> T;
    std::vector<T> triplets;

    triplets.push_back(T(0, 0, 4.0));
    triplets.push_back(T(0, 1, -1.0));
    triplets.push_back(T(1, 0, -1.0));
    triplets.push_back(T(1, 1, 4.0));
    triplets.push_back(T(2, 2, 4.0));

    Eigen::SparseMatrix<double> A_sparse(3, 3);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    std::cout << "Non-zero elements of A:\n";
    for (int k = 0; k < A_sparse.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(A_sparse, k); it; ++it) {
            std::cout << "  (" << it.row() << ", " << it.col() << ") = " << it.value() << "\n";
        }
    }

    return 0;
}
