/**
 * Chapter 2.4: Cholesky Decomposition
 *
 * Topics: A = L * L^T for positive definite matrices
 * SLAM Applications: Covariance matrices, Kalman filter, sampling from Gaussian
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.4 Cholesky Decomposition ===\n";
    cout << "A = L * L^T (A must be positive definite)\n\n";

    // Create a positive definite matrix (covariance matrix)
    Matrix3d cov;
    cov << 4, 2, 1,
           2, 5, 2,
           1, 2, 6;

    // Verify it's positive definite (all eigenvalues > 0)
    SelfAdjointEigenSolver<Matrix3d> eigensolver(cov);
    cout << "Covariance matrix:\n" << cov << "\n\n";
    cout << "Eigenvalues: " << eigensolver.eigenvalues().transpose() << "\n";
    cout << "(All positive -> positive definite)\n\n";

    // Cholesky decomposition
    LLT<Matrix3d> cholesky(cov);
    Matrix3d L = cholesky.matrixL();

    cout << "L (lower triangular):\n" << L << "\n\n";
    cout << "L * L^T (should equal cov):\n" << L * L.transpose() << "\n\n";

    // Use Cholesky to solve Ax = b efficiently
    Vector3d b_vec(1, 2, 3);
    Vector3d x_chol = cholesky.solve(b_vec);
    cout << "Solution to cov * x = b: " << x_chol.transpose() << "\n";
    cout << "Verification cov * x: " << (cov * x_chol).transpose() << "\n";

    return 0;
}
