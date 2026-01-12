/**
 * Chapter 4.8: Practical - Triangulation
 *
 * Topics: Finding 3D point from multiple camera observations
 * SLAM: Essential for stereo vision and multi-view geometry
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.8 Practical: Triangulation ===\n\n";

    // Given point observations from multiple cameras, find 3D point
    // This is a least squares problem

    // Camera 1: at origin, looking along Z
    // Camera 2: at (1, 0, 0), looking along Z

    // Projection matrices (simplified pinhole)
    Eigen::Matrix<double, 3, 4> P1, P2;
    P1 << 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0;

    Eigen::Matrix3d R2 = Eigen::Matrix3d::Identity();
    Eigen::Vector3d t2(1, 0, 0);
    P2 << R2.row(0), -R2.row(0).dot(t2),
          R2.row(1), -R2.row(1).dot(t2),
          R2.row(2), -R2.row(2).dot(t2);

    // True 3D point
    Eigen::Vector3d point_3d(0.5, 0.5, 2.0);

    // Project to get 2D observations (homogeneous)
    Eigen::Vector4d point_homo(point_3d.x(), point_3d.y(), point_3d.z(), 1);
    Eigen::Vector3d obs1 = P1 * point_homo;  obs1 /= obs1(2);
    Eigen::Vector3d obs2 = P2 * point_homo;  obs2 /= obs2(2);

    std::cout << "Observation in camera 1: (" << obs1(0) << ", " << obs1(1) << ")\n";
    std::cout << "Observation in camera 2: (" << obs2(0) << ", " << obs2(1) << ")\n\n";

    // Linear triangulation using DLT
    // Each observation gives 2 equations (from x and y)
    Eigen::Matrix<double, 4, 4> A_tri;
    A_tri.row(0) = obs1(0) * P1.row(2) - P1.row(0);
    A_tri.row(1) = obs1(1) * P1.row(2) - P1.row(1);
    A_tri.row(2) = obs2(0) * P2.row(2) - P2.row(0);
    A_tri.row(3) = obs2(1) * P2.row(2) - P2.row(1);

    // Solve using SVD (homogeneous system, find null space)
    Eigen::JacobiSVD<Eigen::Matrix<double, 4, 4>> svd_tri(A_tri, Eigen::ComputeFullV);
    Eigen::Vector4d X_homo = svd_tri.matrixV().col(3);

    // Convert from homogeneous
    Eigen::Vector3d X_recovered = X_homo.head<3>() / X_homo(3);

    std::cout << "True 3D point: " << point_3d.transpose() << "\n";
    std::cout << "Triangulated:  " << X_recovered.transpose() << "\n";
    std::cout << "Error: " << (X_recovered - point_3d).norm() << "\n";

    return 0;
}
