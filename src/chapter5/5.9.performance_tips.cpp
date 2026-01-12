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

int main() {
    std::cout << "=== 5.9 Performance Tips ===\n\n";

    std::cout << "1. Use triplets for initial construction\n";
    std::cout << "2. Call makeCompressed() after coeffRef modifications\n";
    std::cout << "3. Reserve space if you know the structure\n";
    std::cout << "4. Reuse factorization if matrix structure unchanged\n";
    std::cout << "5. Use analyzePattern() + factorize() for repeated solves\n";
    std::cout << "6. Choose solver based on matrix properties:\n";
    std::cout << "   - SPD: SimplicialLLT or SimplicialLDLT\n";
    std::cout << "   - General: SparseLU or SparseQR\n";
    std::cout << "   - Very large: Iterative (CG, BiCGSTAB)\n\n";

    // Create a sparse matrix
    typedef Eigen::Triplet<double> T;
    std::vector<T> triplets;
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

    Eigen::SparseMatrix<double> A_sparse(5, 5);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    Eigen::VectorXd b_sparse(5);
    b_sparse << 1, 2, 3, 4, 5;

    // Example: Reusing factorization
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> reuse_solver;
    reuse_solver.analyzePattern(A_sparse);  // Do once

    // For each solve with same structure but different values:
    reuse_solver.factorize(A_sparse);  // Faster than compute()
    Eigen::VectorXd x_reuse = reuse_solver.solve(b_sparse);
    std::cout << "Solution with reused pattern: " << x_reuse.transpose() << "\n";

    return 0;
}
