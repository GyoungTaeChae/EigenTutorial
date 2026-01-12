/**
 * Chapter 2.1: SVD (Singular Value Decomposition)
 *
 * Topics: A = U * S * V^T, rank, pseudo-inverse
 * SLAM Applications: Essential/Fundamental matrix, point cloud alignment, null space
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.1 SVD (Singular Value Decomposition) ===\n";
    cout << "A = U * S * V^T\n\n";

    Matrix3d A;
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    // Full SVD
    JacobiSVD<Matrix3d> svd(A, ComputeFullU | ComputeFullV);

    Matrix3d U = svd.matrixU();
    Matrix3d V = svd.matrixV();
    Vector3d singular_values = svd.singularValues();

    cout << "Original matrix A:\n" << A << "\n\n";
    cout << "U:\n" << U << "\n\n";
    cout << "Singular values: " << singular_values.transpose() << "\n\n";
    cout << "V:\n" << V << "\n\n";

    // Reconstruct A = U * S * V^T
    Matrix3d S = Matrix3d::Zero();
    S.diagonal() = singular_values;
    Matrix3d A_reconstructed = U * S * V.transpose();
    cout << "Reconstructed A:\n" << A_reconstructed << "\n\n";

    // Rank from SVD (count non-zero singular values)
    double threshold = 1e-10;
    int rank = (singular_values.array() > threshold).count();
    cout << "Rank of A: " << rank << "\n\n";

    // Pseudo-inverse using SVD
    Matrix3d S_pinv = Matrix3d::Zero();
    for (int i = 0; i < 3; ++i) {
        if (singular_values(i) > threshold) {
            S_pinv(i, i) = 1.0 / singular_values(i);
        }
    }
    Matrix3d A_pinv = V * S_pinv * U.transpose();
    cout << "Pseudo-inverse:\n" << A_pinv << "\n";

    return 0;
}
