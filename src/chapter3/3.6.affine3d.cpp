/**
 * Chapter 3.6: Affine3d
 *
 * Topics: Affine transformations including scaling
 * Use when you need scale, shear, etc.
 */

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.6 Affine3d ===\n\n";

    // Affine transformations include scaling (not just rigid body)

    Eigen::Affine3d A = Eigen::Affine3d::Identity();
    A.linear() = 2.0 * Eigen::Matrix3d::Identity();  // Uniform scale by 2
    A.translation() = Eigen::Vector3d(1, 1, 1);

    std::cout << "Affine (scale + translate):\n" << A.matrix() << "\n\n";

    Eigen::Vector3d point(1, 0, 0);
    Eigen::Vector3d scaled_point = A * point;
    std::cout << "Original point: " << point.transpose() << "\n";
    std::cout << "Scaled point: " << scaled_point.transpose() << "\n";

    return 0;
}
