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

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.2 Quaternion ===\n\n";

    // Quaternion q = w + xi + yj + zk
    // Eigen stores as (x, y, z, w) internally but constructs as (w, x, y, z)

    // Create rotation matrix for reference
    double angle_z = M_PI / 4;  // 45 degrees
    Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    // Create quaternion from rotation matrix
    Quaterniond q1(Rz);
    cout << "Quaternion from Rz:\n";
    cout << "  coeffs (x,y,z,w): " << q1.coeffs().transpose() << "\n";
    cout << "  w: " << q1.w() << ", x: " << q1.x()
         << ", y: " << q1.y() << ", z: " << q1.z() << "\n\n";

    // Create quaternion directly (w, x, y, z)
    Quaterniond q2(1, 0, 0, 0);  // Identity rotation
    cout << "Identity quaternion: " << q2.coeffs().transpose() << "\n\n";

    // Create from angle-axis
    Quaterniond q3(AngleAxisd(M_PI/2, Vector3d::UnitZ()));
    cout << "90 deg around Z: " << q3.coeffs().transpose() << "\n\n";

    // Convert quaternion back to rotation matrix
    Matrix3d R_from_q = q1.toRotationMatrix();
    cout << "Rotation matrix from quaternion:\n" << R_from_q << "\n\n";

    // Quaternion multiplication (composition of rotations)
    Quaterniond q_combined = q1 * q3;  // First q3, then q1
    cout << "Combined rotation: " << q_combined.coeffs().transpose() << "\n\n";

    // Inverse quaternion (conjugate for unit quaternion)
    Quaterniond q_inv = q1.inverse();
    cout << "Inverse: " << q_inv.coeffs().transpose() << "\n";
    cout << "q * q_inv: " << (q1 * q_inv).coeffs().transpose() << " (should be identity)\n\n";

    // Rotate a vector with quaternion
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = q1 * v;  // Same as q1.toRotationMatrix() * v
    cout << "Original vector: " << v.transpose() << "\n";
    cout << "Rotated vector: " << v_rotated.transpose() << "\n\n";

    // IMPORTANT: Normalize quaternion after operations (numerical drift)
    Quaterniond q_unnormalized(0.99, 0.1, 0.0, 0.0);
    cout << "Before normalize, norm: " << q_unnormalized.norm() << "\n";
    q_unnormalized.normalize();
    cout << "After normalize, norm: " << q_unnormalized.norm() << "\n";

    return 0;
}
