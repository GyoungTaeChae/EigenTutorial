/**
 * Chapter 4.1: Square Systems Ax = b
 *
 * Topics: LU, FullPivLU, QR solvers for square matrices
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.1 Square Systems ===\n\n";

    Eigen::Matrix3d A;
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 10;  // Non-singular

    Eigen::Vector3d b(3, 3, 4);

    // Method 1: Direct inverse (AVOID - slow and numerically unstable)
    Eigen::Vector3d x_inv = A.inverse() * b;
    std::cout << "Using inverse (not recommended):\n";
    std::cout << "  x = " << x_inv.transpose() << "\n";
    std::cout << "  Residual |Ax - b|: " << (A * x_inv - b).norm() << "\n\n";

    // Method 2: LU decomposition (general purpose)
    Eigen::Vector3d x_lu = A.partialPivLu().solve(b);
    std::cout << "Using PartialPivLU:\n";
    std::cout << "  x = " << x_lu.transpose() << "\n";
    std::cout << "  Residual: " << (A * x_lu - b).norm() << "\n\n";

    // Method 3: Full pivot LU (more stable, slower)
    Eigen::Vector3d x_fulllu = A.fullPivLu().solve(b);
    std::cout << "Using FullPivLU:\n";
    std::cout << "  x = " << x_fulllu.transpose() << "\n";
    std::cout << "  Residual: " << (A * x_fulllu - b).norm() << "\n\n";

    // Method 4: QR decomposition (good for near-singular matrices)
    Eigen::Vector3d x_qr = A.colPivHouseholderQr().solve(b);
    std::cout << "Using ColPivHouseholderQR:\n";
    std::cout << "  x = " << x_qr.transpose() << "\n";
    std::cout << "  Residual: " << (A * x_qr - b).norm() << "\n";

    return 0;
}
