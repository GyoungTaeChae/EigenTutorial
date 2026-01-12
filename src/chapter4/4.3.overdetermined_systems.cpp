/**
 * Chapter 4.3: Overdetermined Systems (Least Squares)
 *
 * Topics: Normal equations, QR, SVD for least squares
 * SLAM: Line fitting, pose estimation, triangulation
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.3 Overdetermined Systems (Least Squares) ===\n\n";

    // More equations than unknowns: Ax = b has no exact solution
    // Find x that minimizes |Ax - b|^2

    // Example: Fitting a line y = mx + c to noisy data
    // Points: (0, 0.1), (1, 2.1), (2, 3.9), (3, 6.2)
    // Model: [1, x] * [c, m]^T = y

    Eigen::MatrixXd A_ls(4, 2);  // 4 equations, 2 unknowns
    A_ls << 1, 0,
            1, 1,
            1, 2,
            1, 3;

    Eigen::VectorXd b_ls(4);
    b_ls << 0.1, 2.1, 3.9, 6.2;

    std::cout << "Fitting line to points: (0,0.1), (1,2.1), (2,3.9), (3,6.2)\n\n";

    // Method 1: Normal equations (A^T A) x = A^T b
    Eigen::Vector2d x_normal = (A_ls.transpose() * A_ls).ldlt().solve(A_ls.transpose() * b_ls);
    std::cout << "Normal equations:\n";
    std::cout << "  c = " << x_normal(0) << ", m = " << x_normal(1) << "\n";
    std::cout << "  Line: y = " << x_normal(1) << "x + " << x_normal(0) << "\n\n";

    // Method 2: QR decomposition (recommended)
    Eigen::Vector2d x_qr_ls = A_ls.colPivHouseholderQr().solve(b_ls);
    std::cout << "QR decomposition:\n";
    std::cout << "  c = " << x_qr_ls(0) << ", m = " << x_qr_ls(1) << "\n\n";

    // Method 3: SVD (most robust, slowest)
    Eigen::Vector2d x_svd = A_ls.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b_ls);
    std::cout << "SVD:\n";
    std::cout << "  c = " << x_svd(0) << ", m = " << x_svd(1) << "\n\n";

    // Compute residual
    Eigen::VectorXd residual = A_ls * x_qr_ls - b_ls;
    std::cout << "Residuals: " << residual.transpose() << "\n";
    std::cout << "RMS error: " << std::sqrt(residual.squaredNorm() / residual.size()) << "\n";

    return 0;
}
