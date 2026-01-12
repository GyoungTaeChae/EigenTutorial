/**
 * Chapter 4.3: Overdetermined Systems (Least Squares)
 *
 * Topics: Normal equations, QR, SVD for least squares
 * SLAM: Line fitting, pose estimation, triangulation
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.3 Overdetermined Systems (Least Squares) ===\n\n";

    // More equations than unknowns: Ax = b has no exact solution
    // Find x that minimizes |Ax - b|^2

    // Example: Fitting a line y = mx + c to noisy data
    // Points: (0, 0.1), (1, 2.1), (2, 3.9), (3, 6.2)
    // Model: [1, x] * [c, m]^T = y

    MatrixXd A_ls(4, 2);  // 4 equations, 2 unknowns
    A_ls << 1, 0,
            1, 1,
            1, 2,
            1, 3;

    VectorXd b_ls(4);
    b_ls << 0.1, 2.1, 3.9, 6.2;

    cout << "Fitting line to points: (0,0.1), (1,2.1), (2,3.9), (3,6.2)\n\n";

    // Method 1: Normal equations (A^T A) x = A^T b
    Vector2d x_normal = (A_ls.transpose() * A_ls).ldlt().solve(A_ls.transpose() * b_ls);
    cout << "Normal equations:\n";
    cout << "  c = " << x_normal(0) << ", m = " << x_normal(1) << "\n";
    cout << "  Line: y = " << x_normal(1) << "x + " << x_normal(0) << "\n\n";

    // Method 2: QR decomposition (recommended)
    Vector2d x_qr_ls = A_ls.colPivHouseholderQr().solve(b_ls);
    cout << "QR decomposition:\n";
    cout << "  c = " << x_qr_ls(0) << ", m = " << x_qr_ls(1) << "\n\n";

    // Method 3: SVD (most robust, slowest)
    Vector2d x_svd = A_ls.bdcSvd(ComputeThinU | ComputeThinV).solve(b_ls);
    cout << "SVD:\n";
    cout << "  c = " << x_svd(0) << ", m = " << x_svd(1) << "\n\n";

    // Compute residual
    VectorXd residual = A_ls * x_qr_ls - b_ls;
    cout << "Residuals: " << residual.transpose() << "\n";
    cout << "RMS error: " << sqrt(residual.squaredNorm() / residual.size()) << "\n";

    return 0;
}
