/**
 * Chapter 2.7: Essential Matrix Decomposition
 *
 * Topics: Essential matrix properties, SVD constraint enforcement
 * SLAM Applications: Stereo vision, visual odometry, epipolar geometry
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.7 Essential Matrix Decomposition ===\n\n";

    // The Essential matrix E relates corresponding points in stereo:
    // x2^T * E * x1 = 0
    // E = [t]_x * R  (t is translation, R is rotation)
    // E has rank 2 and two equal non-zero singular values

    // Create a synthetic Essential matrix
    Eigen::Matrix3d R_cam;
    double theta_cam = 0.1;  // Small rotation
    R_cam << cos(theta_cam), -sin(theta_cam), 0,
             sin(theta_cam),  cos(theta_cam), 0,
             0,               0,              1;

    Eigen::Vector3d t_cam(1, 0, 0);  // Translation along x-axis
    t_cam.normalize();

    // Skew-symmetric matrix of t
    Eigen::Matrix3d t_skew;
    t_skew <<     0,    -t_cam.z(),  t_cam.y(),
              t_cam.z(),     0,     -t_cam.x(),
             -t_cam.y(),  t_cam.x(),     0;

    Eigen::Matrix3d E = t_skew * R_cam;
    std::cout << "Essential matrix E:\n" << E << "\n\n";

    // SVD of E should give singular values [1, 1, 0] (up to scale)
    Eigen::JacobiSVD<Eigen::Matrix3d> svd_E(E, Eigen::ComputeFullU | Eigen::ComputeFullV);
    std::cout << "Singular values of E: " << svd_E.singularValues().transpose() << "\n";
    std::cout << "(Should be approximately [s, s, 0] for some s)\n\n";

    // Enforce Essential matrix constraint (two equal singular values)
    Eigen::Vector3d sv_corrected(1, 1, 0);
    Eigen::Matrix3d E_corrected = svd_E.matrixU() * sv_corrected.asDiagonal() * svd_E.matrixV().transpose();
    std::cout << "Corrected E:\n" << E_corrected << "\n";

    return 0;
}
