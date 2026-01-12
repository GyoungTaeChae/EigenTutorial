/**
 * Chapter 4.2: Symmetric Positive Definite Systems
 *
 * Topics: LLT (Cholesky), LDLT for SPD matrices
 * SLAM: Covariance matrices, Kalman filter
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.2 Symmetric Positive Definite Systems ===\n\n";

    // For SPD matrices (like covariance matrices), use Cholesky
    // It's 2x faster than LU and more stable

    Matrix3d SPD;
    SPD << 4, 2, 1,
           2, 5, 2,
           1, 2, 6;

    Vector3d b_spd(1, 2, 3);

    // LLT (Cholesky) - fastest for SPD
    Vector3d x_llt = SPD.llt().solve(b_spd);
    cout << "Using LLT (Cholesky):\n";
    cout << "  x = " << x_llt.transpose() << "\n";
    cout << "  Residual: " << (SPD * x_llt - b_spd).norm() << "\n\n";

    // LDLT - slightly more stable, handles semi-definite
    Vector3d x_ldlt = SPD.ldlt().solve(b_spd);
    cout << "Using LDLT:\n";
    cout << "  x = " << x_ldlt.transpose() << "\n";
    cout << "  Residual: " << (SPD * x_ldlt - b_spd).norm() << "\n";

    return 0;
}
