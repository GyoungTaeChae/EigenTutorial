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

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.6 Iterative Solvers ===\n\n";

    // Create larger SPD matrix
    int large_n = 100;
    typedef Triplet<double> T;
    vector<T> large_trips;

    for (int i = 0; i < large_n; ++i) {
        large_trips.push_back(T(i, i, 4.0));  // Diagonal
        if (i > 0) {
            large_trips.push_back(T(i, i-1, -1.0));
            large_trips.push_back(T(i-1, i, -1.0));
        }
    }
    SparseMatrix<double> A_large(large_n, large_n);
    A_large.setFromTriplets(large_trips.begin(), large_trips.end());

    VectorXd b_large = VectorXd::Ones(large_n);

    // Conjugate Gradient
    ConjugateGradient<SparseMatrix<double>, Lower|Upper> cg;
    cg.setMaxIterations(1000);
    cg.setTolerance(1e-10);
    cg.compute(A_large);

    VectorXd x_cg = cg.solve(b_large);
    cout << "Conjugate Gradient:\n";
    cout << "  Iterations: " << cg.iterations() << "\n";
    cout << "  Estimated error: " << cg.error() << "\n";
    cout << "  Residual norm: " << (A_large * x_cg - b_large).norm() << "\n\n";

    // BiCGSTAB for non-symmetric matrices
    BiCGSTAB<SparseMatrix<double>> bicgstab;
    bicgstab.compute(A_large);
    VectorXd x_bicg = bicgstab.solve(b_large);
    cout << "BiCGSTAB:\n";
    cout << "  Iterations: " << bicgstab.iterations() << "\n";
    cout << "  Residual norm: " << (A_large * x_bicg - b_large).norm() << "\n";

    return 0;
}
