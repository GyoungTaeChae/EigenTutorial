/**
 * Chapter 3.9: Practical - Pose Composition Chain
 *
 * Topics: Chaining transformations for robot arm, sensor chains
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.9 Pose Composition Chain ===\n\n";

    // Robot with base, arm link 1, arm link 2, end effector
    // T_world_ee = T_world_base * T_base_link1 * T_link1_link2 * T_link2_ee

    Eigen::Isometry3d T_world_base = Eigen::Isometry3d::Identity();
    T_world_base.translation() = Eigen::Vector3d(1, 0, 0);

    Eigen::Isometry3d T_base_link1 = Eigen::Isometry3d::Identity();
    T_base_link1.rotate(Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitZ()));
    T_base_link1.translation() = Eigen::Vector3d(0.5, 0, 0.1);

    Eigen::Isometry3d T_link1_link2 = Eigen::Isometry3d::Identity();
    T_link1_link2.rotate(Eigen::AngleAxisd(-M_PI/6, Eigen::Vector3d::UnitY()));
    T_link1_link2.translation() = Eigen::Vector3d(0.3, 0, 0);

    Eigen::Isometry3d T_link2_ee = Eigen::Isometry3d::Identity();
    T_link2_ee.translation() = Eigen::Vector3d(0.2, 0, 0);

    // Chain composition
    Eigen::Isometry3d T_world_ee = T_world_base * T_base_link1 * T_link1_link2 * T_link2_ee;

    std::cout << "End effector position in world: "
         << T_world_ee.translation().transpose() << "\n";

    return 0;
}
