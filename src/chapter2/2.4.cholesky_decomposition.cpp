/**
 * Chapter 2.4: Cholesky Decomposition
 *
 * Topics: A = L * L^T for positive definite matrices
 * SLAM Applications: Covariance matrices, Kalman filter, sampling from Gaussian
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.4 Cholesky Decomposition ===\n";
    std::cout << "A = L * L^T (A must be positive definite)\n\n";

    // Create a positive definite matrix (covariance matrix)
    Eigen::Matrix3d cov;
    cov << 4, 2, 1,
           2, 5, 2,
           1, 2, 6;

    // Verify it's positive definite (all eigenvalues > 0)
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver(cov);
    std::cout << "Covariance matrix:\n" << cov << "\n\n";
    std::cout << "Eigenvalues: " << eigensolver.eigenvalues().transpose() << "\n";
    std::cout << "(All positive -> positive definite)\n\n";

    // Cholesky decomposition
    Eigen::LLT<Eigen::Matrix3d> cholesky(cov);
    Eigen::Matrix3d L = cholesky.matrixL();

    std::cout << "L (lower triangular):\n" << L << "\n\n";
    std::cout << "L * L^T (should equal cov):\n" << L * L.transpose() << "\n\n";

    // Use Cholesky to solve Ax = b efficiently
    Eigen::Vector3d b_vec(1, 2, 3);
    Eigen::Vector3d x_chol = cholesky.solve(b_vec);
    std::cout << "Solution to cov * x = b: " << x_chol.transpose() << "\n";
    std::cout << "Verification cov * x: " << (cov * x_chol).transpose() << "\n";

    return 0;
}
