/**
 * Chapter 5.9: Performance Tips for Sparse Matrices
 *
 * Topics: Best practices, analyzePattern, factorize
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.9 Performance Tips ===\n\n";

    cout << "1. Use triplets for initial construction\n";
    cout << "2. Call makeCompressed() after coeffRef modifications\n";
    cout << "3. Reserve space if you know the structure\n";
    cout << "4. Reuse factorization if matrix structure unchanged\n";
    cout << "5. Use analyzePattern() + factorize() for repeated solves\n";
    cout << "6. Choose solver based on matrix properties:\n";
    cout << "   - SPD: SimplicialLLT or SimplicialLDLT\n";
    cout << "   - General: SparseLU or SparseQR\n";
    cout << "   - Very large: Iterative (CG, BiCGSTAB)\n\n";

    // Create a sparse matrix
    typedef Triplet<double> T;
    vector<T> triplets;
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

    SparseMatrix<double> A_sparse(5, 5);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    VectorXd b_sparse(5);
    b_sparse << 1, 2, 3, 4, 5;

    // Example: Reusing factorization
    SimplicialLDLT<SparseMatrix<double>> reuse_solver;
    reuse_solver.analyzePattern(A_sparse);  // Do once

    // For each solve with same structure but different values:
    reuse_solver.factorize(A_sparse);  // Faster than compute()
    VectorXd x_reuse = reuse_solver.solve(b_sparse);
    cout << "Solution with reused pattern: " << x_reuse.transpose() << "\n";

    return 0;
}
