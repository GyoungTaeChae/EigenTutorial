/**
 * Chapter 3.8: Practical - Camera Pose in SLAM
 *
 * Topics: T_world_camera vs T_camera_world, transforming points
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.8 Practical: Camera Pose ===\n\n";

    // In SLAM, camera pose is often represented as:
    // T_world_camera: transforms points from camera frame to world frame
    // or T_camera_world: transforms points from world frame to camera frame

    // World frame origin
    Isometry3d T_world_camera = Isometry3d::Identity();

    // Camera is at position (0, 0, 1) looking down Z-axis
    T_world_camera.translation() = Vector3d(0, 0, 1);

    // Camera is rotated 45 deg around Y-axis (looking slightly left)
    T_world_camera.rotate(AngleAxisd(M_PI/4, Vector3d::UnitY()));

    cout << "Camera pose (T_world_camera):\n" << T_world_camera.matrix() << "\n\n";

    // Point in camera frame
    Vector3d point_camera(0, 0, 1);  // 1 meter in front of camera
    cout << "Point in camera frame: " << point_camera.transpose() << "\n";

    // Transform to world frame
    Vector3d point_world = T_world_camera * point_camera;
    cout << "Point in world frame: " << point_world.transpose() << "\n\n";

    // Inverse: world to camera
    Isometry3d T_camera_world = T_world_camera.inverse();
    Vector3d point_back = T_camera_world * point_world;
    cout << "Back to camera frame: " << point_back.transpose() << "\n";

    return 0;
}
