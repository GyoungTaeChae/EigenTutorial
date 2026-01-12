/**
 * Chapter 4.2: Symmetric Positive Definite Systems
 *
 * Topics: LLT (Cholesky), LDLT for SPD matrices
 * SLAM: Covariance matrices, Kalman filter
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.2 Symmetric Positive Definite Systems ===\n\n";

    // For SPD matrices (like covariance matrices), use Cholesky
    // It's 2x faster than LU and more stable

    Eigen::Matrix3d SPD;
    SPD << 4, 2, 1,
           2, 5, 2,
           1, 2, 6;

    Eigen::Vector3d b_spd(1, 2, 3);

    // LLT (Cholesky) - fastest for SPD
    Eigen::Vector3d x_llt = SPD.llt().solve(b_spd);
    std::cout << "Using LLT (Cholesky):\n";
    std::cout << "  x = " << x_llt.transpose() << "\n";
    std::cout << "  Residual: " << (SPD * x_llt - b_spd).norm() << "\n\n";

    // LDLT - slightly more stable, handles semi-definite
    Eigen::Vector3d x_ldlt = SPD.ldlt().solve(b_spd);
    std::cout << "Using LDLT:\n";
    std::cout << "  x = " << x_ldlt.transpose() << "\n";
    std::cout << "  Residual: " << (SPD * x_ldlt - b_spd).norm() << "\n";

    return 0;
}
