/**
 * Chapter 7.9: SLAM-Specific Patterns
 *
 * Topics: Covariance propagation, information matrices, pose accumulation
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 7.9 SLAM Patterns ===\n\n";

    // Pattern 1: Covariance propagation
    // If y = f(x) and x has covariance P, then y has covariance J*P*J^T
    Eigen::Matrix3d P_in = Eigen::Matrix3d::Identity() * 0.1;  // Input covariance
    Eigen::Matrix<double, 2, 3> J_func;  // Jacobian of some function
    J_func << 1, 0, 0.5,
              0, 1, 0.3;
    Eigen::Matrix2d P_out = J_func * P_in * J_func.transpose();
    std::cout << "Covariance propagation: P_out = J * P_in * J^T\n";
    std::cout << "P_out:\n" << P_out << "\n\n";

    // Pattern 2: Information (inverse covariance) matrices
    Eigen::Matrix3d Info = P_in.inverse();
    std::cout << "Information matrix:\n" << Info << "\n\n";

    // Pattern 3: Efficient pose inverse
    // For SE(3): T^{-1} = [R^T | -R^T * t]
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
    T.rotate(Eigen::AngleAxisd(0.5, Eigen::Vector3d::UnitZ()));
    T.translation() = Eigen::Vector3d(1, 2, 3);

    Eigen::Isometry3d T_inv = T.inverse();  // Efficient for Isometry
    std::cout << "Pose inverse (efficient for Isometry3d):\n";
    std::cout << "T * T^{-1}:\n" << (T * T_inv).matrix() << "\n\n";

    // Pattern 4: Accumulating transformations
    std::vector<Eigen::Isometry3d, Eigen::aligned_allocator<Eigen::Isometry3d>> trajectory;
    Eigen::Isometry3d current_pose = Eigen::Isometry3d::Identity();
    trajectory.push_back(current_pose);

    // Simulate odometry updates
    for (int i = 0; i < 5; ++i) {
        Eigen::Isometry3d delta = Eigen::Isometry3d::Identity();
        delta.translation() = Eigen::Vector3d(1, 0, 0);  // Move forward
        delta.rotate(Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()));  // Slight turn

        current_pose = current_pose * delta;  // Accumulate
        trajectory.push_back(current_pose);
    }

    std::cout << "Accumulated trajectory positions:\n";
    for (size_t i = 0; i < trajectory.size(); ++i) {
        std::cout << "  Pose " << i << ": " << trajectory[i].translation().transpose() << "\n";
    }

    return 0;
}
