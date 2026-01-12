/**
 * Chapter 5.6: Iterative Solvers
 *
 * Topics: Conjugate Gradient, BiCGSTAB for large systems
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>

int main() {
    std::cout << "=== 5.6 Iterative Solvers ===\n\n";

    // Create larger SPD matrix
    int large_n = 100;
    typedef Eigen::Triplet<double> T;
    std::vector<T> large_trips;

    for (int i = 0; i < large_n; ++i) {
        large_trips.push_back(T(i, i, 4.0));  // Diagonal
        if (i > 0) {
            large_trips.push_back(T(i, i-1, -1.0));
            large_trips.push_back(T(i-1, i, -1.0));
        }
    }
    Eigen::SparseMatrix<double> A_large(large_n, large_n);
    A_large.setFromTriplets(large_trips.begin(), large_trips.end());

    Eigen::VectorXd b_large = Eigen::VectorXd::Ones(large_n);

    // Conjugate Gradient
    Eigen::ConjugateGradient<Eigen::SparseMatrix<double>, Eigen::Lower|Eigen::Upper> cg;
    cg.setMaxIterations(1000);
    cg.setTolerance(1e-10);
    cg.compute(A_large);

    Eigen::VectorXd x_cg = cg.solve(b_large);
    std::cout << "Conjugate Gradient:\n";
    std::cout << "  Iterations: " << cg.iterations() << "\n";
    std::cout << "  Estimated error: " << cg.error() << "\n";
    std::cout << "  Residual norm: " << (A_large * x_cg - b_large).norm() << "\n\n";

    // BiCGSTAB for non-symmetric matrices
    Eigen::BiCGSTAB<Eigen::SparseMatrix<double>> bicgstab;
    bicgstab.compute(A_large);
    Eigen::VectorXd x_bicg = bicgstab.solve(b_large);
    std::cout << "BiCGSTAB:\n";
    std::cout << "  Iterations: " << bicgstab.iterations() << "\n";
    std::cout << "  Residual norm: " << (A_large * x_bicg - b_large).norm() << "\n";

    return 0;
}
