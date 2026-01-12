/**
 * Chapter 6.9: Simple Bundle Adjustment Problem
 *
 * Topics: Setting up BA problem structure
 * SLAM: Core of visual SLAM backend
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 6.9 Simple BA Problem ===\n\n";

    // Minimal BA: 1 camera, 3 3D points, 3 observations
    // Optimize camera pose and point positions

    // Camera intrinsics
    double fx = 500, fy = 500, cx = 320, cy = 240;

    auto project = [&](const Eigen::Vector3d& P) -> Eigen::Vector2d {
        return Eigen::Vector2d(fx * P.x() / P.z() + cx,
                        fy * P.y() / P.z() + cy);
    };

    // True values
    Eigen::Matrix3d R_ba_true = Eigen::AngleAxisd(0.1, Eigen::Vector3d(1, 0, 0).normalized()).toRotationMatrix();
    Eigen::Vector3d t_ba_true(0.1, 0.2, 0.0);

    std::vector<Eigen::Vector3d> points_true = {
        Eigen::Vector3d(0, 0, 5),
        Eigen::Vector3d(1, 0, 5),
        Eigen::Vector3d(0, 1, 5)
    };

    // Generate observations
    std::vector<Eigen::Vector2d> observations;
    for (const auto& pt : points_true) {
        Eigen::Vector3d pc = R_ba_true * pt + t_ba_true;
        observations.push_back(project(pc));
    }

    std::cout << "True pose: t = " << t_ba_true.transpose() << "\n";
    std::cout << "Observations:\n";
    for (size_t i = 0; i < observations.size(); ++i) {
        std::cout << "  Point " << i << ": " << observations[i].transpose() << "\n";
    }
    std::cout << "\nThis setup is ready for Gauss-Newton optimization.\n";
    std::cout << "Full implementation requires libraries like Ceres or g2o.\n";

    return 0;
}
