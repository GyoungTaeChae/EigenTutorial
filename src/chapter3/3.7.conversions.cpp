/**
 * Chapter 3.7: Conversions Between Representations
 *
 * Topics: Converting between rotation matrix, quaternion, angle-axis, rotation vector
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.7 Conversions Between Representations ===\n\n";

    // Original rotation
    double theta = M_PI / 6;  // 30 degrees around Z
    Eigen::AngleAxisd original(theta, Eigen::Vector3d::UnitZ());

    // To all representations
    Eigen::Matrix3d as_matrix = original.toRotationMatrix(); // angle-axis to matrix
    Eigen::Quaterniond as_quat(original); // angle-axis to quaternion
    Eigen::Vector3d as_rotvec = original.angle() * original.axis(); // angle-axis to rotation vector

    std::cout << "Original: " << theta * 180 / M_PI << " deg around Z\n\n";
    std::cout << "As matrix:\n" << as_matrix << "\n\n";
    std::cout << "As quaternion (x,y,z,w): " << as_quat.coeffs().transpose() << "\n\n";
    std::cout << "As rotation vector: " << as_rotvec.transpose() << "\n\n";

    // From quaternion to others
    Eigen::Matrix3d mat_from_quat = as_quat.toRotationMatrix();
    Eigen::AngleAxisd aa_from_quat(as_quat);

    // From matrix to others
    Eigen::Quaterniond quat_from_mat(as_matrix);
    Eigen::AngleAxisd aa_from_mat(as_matrix);

    std::cout << "All conversions consistent: "
         << ((mat_from_quat - as_matrix).norm() < 1e-10 ? "YES" : "NO") << "\n";

    return 0;
}
