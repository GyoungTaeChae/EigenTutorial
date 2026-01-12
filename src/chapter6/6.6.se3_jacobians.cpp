/**
 * Chapter 6.6: SE(3) Jacobians
 *
 * Topics: Jacobians for pose transformations
 * SLAM: Essential for pose optimization
 */

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

// Skew-symmetric matrix
Eigen::Matrix3d skew(const Eigen::Vector3d& v) {
    Eigen::Matrix3d m;
    m <<     0, -v.z(),  v.y(),
         v.z(),      0, -v.x(),
        -v.y(),  v.x(),      0;
    return m;
}

int main() {
    std::cout << "=== 6.6 SE(3) Jacobians ===\n\n";

    // In SLAM, we optimize poses T = [R|t] in SE(3)
    // The pose is parameterized by 6 DOF: [translation, rotation]
    // Rotation uses small angle approximation (lie algebra)

    // Point transformation: p' = R * p + t
    // Jacobian w.r.t. pose increment [dt, dw]:
    //   dp'/dt = I  (3x3)
    //   dp'/dw = -R * [p]_x  (3x3)

    Eigen::Vector3d p(1, 2, 3);  // Point in local frame
    Eigen::Matrix3d R = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Vector3d t(0.5, 0, 0);

    Eigen::Vector3d p_transformed = R * p + t;
    std::cout << "Original point: " << p.transpose() << "\n";
    std::cout << "Transformed: " << p_transformed.transpose() << "\n\n";

    // Jacobian of transformation w.r.t. pose (3x6)
    Eigen::Matrix<double, 3, 6> J_pose;
    J_pose.block<3, 3>(0, 0) = Eigen::Matrix3d::Identity();  // d(p')/dt
    J_pose.block<3, 3>(0, 3) = -R * skew(p);         // d(p')/dw

    std::cout << "Jacobian d(p')/d(pose) [3x6]:\n" << J_pose << "\n\n";

    // Verify numerically
    Eigen::Matrix<double, 3, 6> J_pose_num;
    double eps_pose = 1e-6;

    // Translation perturbations
    for (int i = 0; i < 3; ++i) {
        Eigen::Vector3d t_plus = t;
        t_plus(i) += eps_pose;
        Eigen::Vector3d p_plus = R * p + t_plus;
        J_pose_num.col(i) = (p_plus - p_transformed) / eps_pose;
    }

    // Rotation perturbations
    for (int i = 0; i < 3; ++i) {
        Eigen::Matrix3d R_pert = R * Eigen::AngleAxisd(eps_pose, Eigen::Vector3d::Unit(i)).toRotationMatrix();
        Eigen::Vector3d p_plus = R_pert * p + t;
        J_pose_num.col(3 + i) = (p_plus - p_transformed) / eps_pose;
    }

    std::cout << "Numerical Jacobian:\n" << J_pose_num << "\n";
    std::cout << "Error: " << (J_pose - J_pose_num).norm() << "\n";

    return 0;
}
