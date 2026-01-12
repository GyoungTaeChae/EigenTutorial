/**
 * Chapter 3.5: Isometry3d (SE3 - Rigid Body Transformation)
 *
 * Topics: SE(3) = rotation + translation, preserves distances
 * SLAM: Represents camera/robot poses
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.5 Isometry3d (SE3) ===\n\n";

    // SE(3) = Special Euclidean group: rotation + translation
    // Isometry preserves distances (rigid body motion)

    // Create rotation for use
    double angle_z = M_PI / 4;
    Eigen::Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;
    Eigen::Quaterniond q1(Rz);

    // Create identity transformation
    Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity();

    // Set rotation using quaternion
    T1.rotate(q1);

    // Set translation
    T1.pretranslate(Eigen::Vector3d(1, 2, 3));

    std::cout << "Transformation matrix:\n" << T1.matrix() << "\n\n";

    // Extract rotation and translation
    Eigen::Matrix3d R_extracted = T1.rotation();
    Eigen::Vector3d t_extracted = T1.translation();
    std::cout << "Extracted rotation:\n" << R_extracted << "\n\n";
    std::cout << "Extracted translation: " << t_extracted.transpose() << "\n\n";

    // Build transformation step by step
    Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
    T2.linear() = Rz;                    // Set rotation part
    T2.translation() = Eigen::Vector3d(4, 5, 6); // Set translation part
    std::cout << "T2 matrix:\n" << T2.matrix() << "\n\n";

    // Transform a point
    Eigen::Vector3d point(1, 0, 0);
    Eigen::Vector3d transformed_point = T2 * point;  // R * p + t
    std::cout << "Original point: " << point.transpose() << "\n";
    std::cout << "Transformed point: " << transformed_point.transpose() << "\n\n";

    // Composition of transformations
    Eigen::Isometry3d T_combined = T1 * T2;  // First T2, then T1
    std::cout << "Combined transformation:\n" << T_combined.matrix() << "\n\n";

    // Inverse transformation
    Eigen::Isometry3d T_inv = T1.inverse();
    std::cout << "T1 * T1_inv (should be identity):\n" << (T1 * T_inv).matrix() << "\n";

    return 0;
}
