/**
 * Chapter 2.6: Eigenvalue Decomposition
 *
 * Topics: A = V * D * V^(-1), eigenvalues and eigenvectors
 * SLAM Applications: PCA, covariance analysis, camera calibration
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.6 Eigenvalue Decomposition ===\n";
    std::cout << "A = V * D * V^(-1)\n\n";

    // For symmetric matrices (like covariance), use SelfAdjointEigenSolver
    Eigen::Matrix3d sym;
    sym << 3, 1, 1,
           1, 3, 1,
           1, 1, 3;

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eig_sym(sym);
    std::cout << "Symmetric matrix:\n" << sym << "\n\n";
    std::cout << "Eigenvalues: " << eig_sym.eigenvalues().transpose() << "\n\n";
    std::cout << "Eigenvectors:\n" << eig_sym.eigenvectors() << "\n\n";

    // Verify: A * v = lambda * v
    Eigen::Vector3d v1 = eig_sym.eigenvectors().col(0);
    double lambda1 = eig_sym.eigenvalues()(0);
    std::cout << "A * v1: " << (sym * v1).transpose() << "\n";
    std::cout << "lambda1 * v1: " << (lambda1 * v1).transpose() << "\n\n";

    // For general matrices, use EigenSolver
    Eigen::Matrix3d general;
    general << 0, 1, 0,
              -1, 0, 0,
               0, 0, 1;  // Rotation-like matrix (has complex eigenvalues)

    Eigen::EigenSolver<Eigen::Matrix3d> eig_gen(general);
    std::cout << "General matrix:\n" << general << "\n\n";
    std::cout << "Eigenvalues (complex): " << eig_gen.eigenvalues().transpose() << "\n";

    return 0;
}
