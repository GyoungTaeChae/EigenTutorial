/**
 * Chapter 2.2: SVD Application - Point Cloud Alignment
 *
 * Topics: Procrustes problem, finding R and t given corresponding point clouds
 * SLAM Application: ICP (Iterative Closest Point) algorithm core
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.2 SVD Application: Point Cloud Alignment ===\n\n";

    // Given two point clouds P and Q, find R, t such that Q = R*P + t
    // This is the Procrustes problem, solved with SVD

    // Source points (P)
    MatrixXd P(3, 4);
    P << 0, 1, 0, 1,
         0, 0, 1, 1,
         0, 0, 0, 0;

    // Create a known transformation
    Matrix3d R_true;
    double angle = M_PI / 4;  // 45 degrees
    R_true << cos(angle), -sin(angle), 0,
              sin(angle),  cos(angle), 0,
              0,           0,          1;
    Vector3d t_true(1, 2, 0);

    // Target points (Q = R*P + t)
    MatrixXd Q(3, 4);
    for (int i = 0; i < 4; ++i) {
        Q.col(i) = R_true * P.col(i) + t_true;
    }

    cout << "Source points P:\n" << P << "\n\n";
    cout << "Target points Q:\n" << Q << "\n\n";

    // Step 1: Compute centroids
    Vector3d centroid_P = P.rowwise().mean();
    Vector3d centroid_Q = Q.rowwise().mean();
    cout << "Centroid P: " << centroid_P.transpose() << "\n";
    cout << "Centroid Q: " << centroid_Q.transpose() << "\n\n";

    // Step 2: Center the points
    MatrixXd P_centered = P.colwise() - centroid_P;
    MatrixXd Q_centered = Q.colwise() - centroid_Q;

    // Step 3: Compute H = P_centered * Q_centered^T
    Matrix3d H = P_centered * Q_centered.transpose();

    // Step 4: SVD of H
    JacobiSVD<Matrix3d> svd_align(H, ComputeFullU | ComputeFullV);

    // Step 5: R = V * U^T
    Matrix3d R_computed = svd_align.matrixV() * svd_align.matrixU().transpose();

    // Handle reflection case (ensure det(R) = 1)
    if (R_computed.determinant() < 0) {
        Matrix3d V_corrected = svd_align.matrixV();
        V_corrected.col(2) *= -1;
        R_computed = V_corrected * svd_align.matrixU().transpose();
    }

    // Step 6: t = centroid_Q - R * centroid_P
    Vector3d t_computed = centroid_Q - R_computed * centroid_P;

    cout << "Computed R:\n" << R_computed << "\n\n";
    cout << "True R:\n" << R_true << "\n\n";
    cout << "Computed t: " << t_computed.transpose() << "\n";
    cout << "True t: " << t_true.transpose() << "\n";

    return 0;
}
