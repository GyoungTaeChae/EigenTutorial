/**
 * Chapter 2.6: Eigenvalue Decomposition
 *
 * Topics: A = V * D * V^(-1), eigenvalues and eigenvectors
 * SLAM Applications: PCA, covariance analysis, camera calibration
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.6 Eigenvalue Decomposition ===\n";
    cout << "A = V * D * V^(-1)\n\n";

    // For symmetric matrices (like covariance), use SelfAdjointEigenSolver
    Matrix3d sym;
    sym << 3, 1, 1,
           1, 3, 1,
           1, 1, 3;

    SelfAdjointEigenSolver<Matrix3d> eig_sym(sym);
    cout << "Symmetric matrix:\n" << sym << "\n\n";
    cout << "Eigenvalues: " << eig_sym.eigenvalues().transpose() << "\n\n";
    cout << "Eigenvectors:\n" << eig_sym.eigenvectors() << "\n\n";

    // Verify: A * v = lambda * v
    Vector3d v1 = eig_sym.eigenvectors().col(0);
    double lambda1 = eig_sym.eigenvalues()(0);
    cout << "A * v1: " << (sym * v1).transpose() << "\n";
    cout << "lambda1 * v1: " << (lambda1 * v1).transpose() << "\n\n";

    // For general matrices, use EigenSolver
    Matrix3d general;
    general << 0, 1, 0,
              -1, 0, 0,
               0, 0, 1;  // Rotation-like matrix (has complex eigenvalues)

    EigenSolver<Matrix3d> eig_gen(general);
    cout << "General matrix:\n" << general << "\n\n";
    cout << "Eigenvalues (complex): " << eig_gen.eigenvalues().transpose() << "\n";

    return 0;
}
