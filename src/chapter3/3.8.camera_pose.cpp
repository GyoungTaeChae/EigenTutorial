/**
 * Chapter 3.8: Practical - Camera Pose in SLAM
 *
 * Topics: T_world_camera vs T_camera_world, transforming points
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.8 Practical: Camera Pose ===\n\n";

    // In SLAM, camera pose is often represented as:
    // T_world_camera: transforms points from camera frame to world frame
    // or T_camera_world: transforms points from world frame to camera frame

    // World frame origin
    Eigen::Isometry3d T_world_camera = Eigen::Isometry3d::Identity();

    // Camera is at position (0, 0, 1) looking down Z-axis
    T_world_camera.translation() = Eigen::Vector3d(0, 0, 1);

    // Camera is rotated 45 deg around Y-axis (looking slightly left)
    T_world_camera.rotate(Eigen::AngleAxisd(M_PI/4, Eigen::Vector3d::UnitY()));

    std::cout << "Camera pose (T_world_camera):\n" << T_world_camera.matrix() << "\n\n";

    // Point in camera frame
    Eigen::Vector3d point_camera(0, 0, 1);  // 1 meter in front of camera
    std::cout << "Point in camera frame: " << point_camera.transpose() << "\n";

    // Transform to world frame
    Eigen::Vector3d point_world = T_world_camera * point_camera;
    std::cout << "Point in world frame: " << point_world.transpose() << "\n\n";

    // Inverse: world to camera
    Eigen::Isometry3d T_camera_world = T_world_camera.inverse();
    Eigen::Vector3d point_back = T_camera_world * point_world;
    std::cout << "Back to camera frame: " << point_back.transpose() << "\n";

    return 0;
}
