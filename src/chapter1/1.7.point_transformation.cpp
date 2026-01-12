/**
 * Chapter 1.7: Practical Example - 3D Point Transformation
 *
 * Topics: Rotation matrix construction, point transformation, homogeneous coordinates
 * Essential for SLAM: transforming points between coordinate frames
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 1.7 Practical: Point Transformation ===\n\n";

    // Define a rotation (90 degrees around Z-axis)
    Eigen::Matrix3d Rz;
    double theta = M_PI / 2;  // 90 degrees
    Rz << std::cos(theta), -std::sin(theta), 0,
          std::sin(theta),  std::cos(theta), 0,
          0,                0,               1;

    // Define translation
    Eigen::Vector3d trans(1, 0, 0);

    // Original point
    Eigen::Vector3d point(1, 0, 0);
    std::cout << "Original point: " << point.transpose() << "\n";

    // Transform: p' = R * p + t
    Eigen::Vector3d transformed = Rz * point + trans;

    std::cout << "Transformed point: " << transformed.transpose() << "\n";

    // Using homogeneous coordinates (4x4 transformation)
    Eigen::Matrix4d T_homo = Eigen::Matrix4d::Identity();
    T_homo.block<3,3>(0,0) = Rz;
    T_homo.block<3,1>(0,3) = trans;

    std::cout << "\nHomogeneous transformation matrix:\n" << T_homo << "\n\n";

    Eigen::Vector4d point_homo(point.x(), point.y(), point.z(), 1.0);
    Eigen::Vector4d transformed_homo = T_homo * point_homo;
    std::cout << "Transformed (homogeneous): " << transformed_homo.head<3>().transpose() << "\n";

    return 0;
}
