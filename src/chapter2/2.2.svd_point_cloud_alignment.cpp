/**
 * Chapter 2.2: SVD Application - Point Cloud Alignment
 *
 * Topics: Procrustes problem, finding R and t given corresponding point clouds
 * SLAM Application: ICP (Iterative Closest Point) algorithm core
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.2 SVD Application: Point Cloud Alignment ===\n\n";

    // Given two point clouds P and Q, find R, t such that Q = R*P + t
    // This is the Procrustes problem, solved with SVD

    // Source points (P)
    Eigen::MatrixXd P(3, 4);
    P << 0, 1, 0, 1,
         0, 0, 1, 1,
         0, 0, 0, 0;

    // Create a known transformation
    Eigen::Matrix3d R_true;
    double angle = M_PI / 4;  // 45 degrees
    R_true << cos(angle), -sin(angle), 0,
              sin(angle),  cos(angle), 0,
              0,           0,          1;
    Eigen::Vector3d t_true(1, 2, 0);

    // Target points (Q = R*P + t)
    Eigen::MatrixXd Q(3, 4);
    for (int i = 0; i < 4; ++i) {
        Q.col(i) = R_true * P.col(i) + t_true;
    }

    std::cout << "Source points P:\n" << P << "\n\n";
    std::cout << "Target points Q:\n" << Q << "\n\n";

    // Step 1: Compute centroids
    Eigen::Vector3d centroid_P = P.rowwise().mean();
    Eigen::Vector3d centroid_Q = Q.rowwise().mean();
    std::cout << "Centroid P: " << centroid_P.transpose() << "\n";
    std::cout << "Centroid Q: " << centroid_Q.transpose() << "\n\n";

    // Step 2: Center the points
    Eigen::MatrixXd P_centered = P.colwise() - centroid_P;
    Eigen::MatrixXd Q_centered = Q.colwise() - centroid_Q;

    // Step 3: Compute H = P_centered * Q_centered^T
    Eigen::Matrix3d H = P_centered * Q_centered.transpose();

    // Step 4: SVD of H
    Eigen::JacobiSVD<Eigen::Matrix3d> svd_align(H, Eigen::ComputeFullU | Eigen::ComputeFullV);

    // Step 5: R = V * U^T
    Eigen::Matrix3d R_computed = svd_align.matrixV() * svd_align.matrixU().transpose();

    // Handle reflection case (ensure det(R) = 1)
    if (R_computed.determinant() < 0) {
        Eigen::Matrix3d V_corrected = svd_align.matrixV();
        V_corrected.col(2) *= -1;
        R_computed = V_corrected * svd_align.matrixU().transpose();
    }

    // Step 6: t = centroid_Q - R * centroid_P
    Eigen::Vector3d t_computed = centroid_Q - R_computed * centroid_P;

    std::cout << "Computed R:\n" << R_computed << "\n\n";
    std::cout << "True R:\n" << R_true << "\n\n";
    std::cout << "Computed t: " << t_computed.transpose() << "\n";
    std::cout << "True t: " << t_true.transpose() << "\n";

    return 0;
}
