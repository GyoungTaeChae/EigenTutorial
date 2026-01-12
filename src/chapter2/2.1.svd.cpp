/**
 * Chapter 2.1: SVD (Singular Value Decomposition)
 *
 * Topics: A = U * S * V^T, rank, pseudo-inverse
 * SLAM Applications: Essential/Fundamental matrix, point cloud alignment, null space
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.1 SVD (Singular Value Decomposition) ===\n";
    std::cout << "A = U * S * V^T\n\n";

    Eigen::Matrix3d A;
    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    // Full SVD
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);

    Eigen::Matrix3d U = svd.matrixU();
    Eigen::Matrix3d V = svd.matrixV();
    Eigen::Vector3d singular_values = svd.singularValues();

    std::cout << "Original matrix A:\n" << A << "\n\n";
    std::cout << "U:\n" << U << "\n\n";
    std::cout << "Singular values: " << singular_values.transpose() << "\n\n";
    std::cout << "V:\n" << V << "\n\n";

    // Reconstruct A = U * S * V^T
    Eigen::Matrix3d S = Eigen::Matrix3d::Zero();
    S.diagonal() = singular_values;
    Eigen::Matrix3d A_reconstructed = U * S * V.transpose();
    std::cout << "Reconstructed A:\n" << A_reconstructed << "\n\n";

    // Rank from SVD (count non-zero singular values)
    double threshold = 1e-10;
    int rank = (singular_values.array() > threshold).count();
    std::cout << "Rank of A: " << rank << "\n\n";

    // Pseudo-inverse using SVD
    Eigen::Matrix3d S_pinv = Eigen::Matrix3d::Zero();
    for (int i = 0; i < 3; ++i) {
        if (singular_values(i) > threshold) {
            S_pinv(i, i) = 1.0 / singular_values(i);
        }
    }
    Eigen::Matrix3d A_pinv = V * S_pinv * U.transpose();
    std::cout << "Pseudo-inverse:\n" << A_pinv << "\n";

    return 0;
}
