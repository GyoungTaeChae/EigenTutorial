/**
 * Chapter 3.2: Quaternion
 *
 * Topics: Quaternion creation, operations, conversion
 * Advantages: Compact, no gimbal lock, easy interpolation, numerically stable
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 3.2 Quaternion ===\n\n";

    // Quaternion q = w + xi + yj + zk
    // Eigen stores as (x, y, z, w) internally but constructs as (w, x, y, z)

    // Create rotation matrix for reference
    double angle_z = M_PI / 4;  // 45 degrees
    Eigen::Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    // Create quaternion from rotation matrix
    Eigen::Quaterniond q1(Rz);
    std::cout << "Quaternion from Rz:\n";
    std::cout << "  coeffs (x,y,z,w): " << q1.coeffs().transpose() << "\n";
    std::cout << "  w: " << q1.w() << ", x: " << q1.x()
         << ", y: " << q1.y() << ", z: " << q1.z() << "\n\n";

    // Create quaternion directly (w, x, y, z)
    Eigen::Quaterniond q2(1, 0, 0, 0);  // Identity rotation
    std::cout << "Identity quaternion: " << q2.coeffs().transpose() << "\n\n";

    // Create from angle-axis
    Eigen::Quaterniond q3(Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d::UnitZ()));
    std::cout << "90 deg around Z: " << q3.coeffs().transpose() << "\n\n";

    // Convert quaternion back to rotation matrix
    Eigen::Matrix3d R_from_q = q1.toRotationMatrix();
    std::cout << "Rotation matrix from quaternion:\n" << R_from_q << "\n\n";

    // Quaternion multiplication (composition of rotations)
    Eigen::Quaterniond q_combined = q1 * q3;  // First q3, then q1
    std::cout << "Combined rotation: " << q_combined.coeffs().transpose() << "\n\n";

    // Inverse quaternion (conjugate for unit quaternion)
    Eigen::Quaterniond q_inv = q1.inverse();
    std::cout << "Inverse: " << q_inv.coeffs().transpose() << "\n";
    std::cout << "q * q_inv: " << (q1 * q_inv).coeffs().transpose() << " (should be identity)\n\n";

    // Rotate a vector with quaternion
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = q1 * v;  // Same as q1.toRotationMatrix() * v
    std::cout << "Original vector: " << v.transpose() << "\n";
    std::cout << "Rotated vector: " << v_rotated.transpose() << "\n\n";

    // IMPORTANT: Normalize quaternion after operations (numerical drift)
    Eigen::Quaterniond q_unnormalized(0.99, 0.1, 0.0, 0.0);
    std::cout << "Before normalize, norm: " << q_unnormalized.norm() << "\n";
    q_unnormalized.normalize();
    std::cout << "After normalize, norm: " << q_unnormalized.norm() << "\n";

    return 0;
}
