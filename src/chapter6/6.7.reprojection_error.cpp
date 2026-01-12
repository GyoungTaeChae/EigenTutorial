/**
 * Chapter 6.7: Reprojection Error Jacobian
 *
 * Topics: Jacobians for visual SLAM optimization
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
    std::cout << "=== 6.7 Reprojection Error Jacobian ===\n\n";

    // In visual SLAM, we minimize reprojection error:
    // e = observed_2d - project(transform(P_3d, pose))

    // Camera intrinsics (simplified)
    double fx = 500, fy = 500, cx = 320, cy = 240;

    // Projection function
    auto project = [&](const Eigen::Vector3d& P) -> Eigen::Vector2d {
        return Eigen::Vector2d(fx * P.x() / P.z() + cx,
                        fy * P.y() / P.z() + cy);
    };

    // 3D point in world frame
    Eigen::Vector3d P_world(0.5, 0.3, 2.0);

    // Camera pose (world to camera)
    Eigen::Matrix3d R_cam = Eigen::Matrix3d::Identity();
    Eigen::Vector3d t_cam(0, 0, 0);

    // Transform to camera frame
    Eigen::Vector3d P_cam = R_cam * P_world + t_cam;

    // Project
    Eigen::Vector2d projected = project(P_cam);
    std::cout << "3D point (world): " << P_world.transpose() << "\n";
    std::cout << "3D point (camera): " << P_cam.transpose() << "\n";
    std::cout << "Projected 2D: " << projected.transpose() << "\n\n";

    // Jacobian of projection w.r.t. camera point (2x3)
    Eigen::Matrix<double, 2, 3> J_proj;
    double X = P_cam.x(), Y = P_cam.y(), Z = P_cam.z();
    J_proj << fx/Z,    0,  -fx*X/(Z*Z),
                 0, fy/Z,  -fy*Y/(Z*Z);

    std::cout << "Jacobian d(uv)/d(P_cam) [2x3]:\n" << J_proj << "\n\n";

    // Jacobian of transformation w.r.t. pose (3x6)
    Eigen::Matrix<double, 3, 6> J_pose;
    J_pose.block<3, 3>(0, 0) = Eigen::Matrix3d::Identity();
    J_pose.block<3, 3>(0, 3) = -R_cam * skew(P_world);

    // Jacobian of reprojection error w.r.t. pose (2x6)
    Eigen::Matrix<double, 2, 6> J_reproj_pose = J_proj * J_pose;
    std::cout << "Jacobian d(uv)/d(pose) [2x6]:\n" << J_reproj_pose << "\n\n";

    // Jacobian w.r.t. 3D point (2x3)
    Eigen::Matrix<double, 2, 3> J_reproj_point = J_proj * R_cam;
    std::cout << "Jacobian d(uv)/d(P_world) [2x3]:\n" << J_reproj_point << "\n";

    return 0;
}
