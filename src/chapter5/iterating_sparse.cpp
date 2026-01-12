/**
 * Chapter 5.4: Iterating Over Sparse Matrices
 *
 * Topics: InnerIterator for accessing non-zero elements
 */

#include <iostream>
#include <vector>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.4 Iterating Over Sparse Elements ===\n\n";

    // Create a sparse matrix
    typedef Triplet<double> T;
    vector<T> triplets;

    triplets.push_back(T(0, 0, 4.0));
    triplets.push_back(T(0, 1, -1.0));
    triplets.push_back(T(1, 0, -1.0));
    triplets.push_back(T(1, 1, 4.0));
    triplets.push_back(T(2, 2, 4.0));

    SparseMatrix<double> A_sparse(3, 3);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    cout << "Non-zero elements of A:\n";
    for (int k = 0; k < A_sparse.outerSize(); ++k) {
        for (SparseMatrix<double>::InnerIterator it(A_sparse, k); it; ++it) {
            cout << "  (" << it.row() << ", " << it.col() << ") = " << it.value() << "\n";
        }
    }

    return 0;
}
