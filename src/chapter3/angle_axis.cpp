/**
 * Chapter 3.3: Angle-Axis (Rodrigues' formula)
 *
 * Topics: Rotation by angle theta around axis n
 * Also known as rotation vector in SLAM optimization
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.3 Angle-Axis ===\n\n";

    // Create angle-axis
    AngleAxisd aa1(M_PI/3, Vector3d::UnitX());  // 60 deg around X
    cout << "Angle: " << aa1.angle() * 180 / M_PI << " degrees\n";
    cout << "Axis: " << aa1.axis().transpose() << "\n\n";

    // Create rotation matrix for reference
    double angle_z = M_PI / 4;  // 45 degrees
    Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    // Create from rotation matrix
    AngleAxisd aa2(Rz);
    cout << "From Rz - Angle: " << aa2.angle() * 180 / M_PI << " degrees\n";
    cout << "From Rz - Axis: " << aa2.axis().transpose() << "\n\n";

    // Convert to rotation matrix
    Matrix3d R_from_aa = aa1.toRotationMatrix();
    cout << "Rotation matrix from angle-axis:\n" << R_from_aa << "\n\n";

    // Rotation vector (axis * angle) - common in SLAM optimization
    Vector3d rotation_vector = aa2.angle() * aa2.axis();
    cout << "Rotation vector: " << rotation_vector.transpose() << "\n\n";

    // Reconstruct from rotation vector
    double angle_from_vec = rotation_vector.norm();
    Vector3d axis_from_vec = rotation_vector.normalized();
    AngleAxisd aa_reconstructed(angle_from_vec, axis_from_vec);
    cout << "Reconstructed angle: " << aa_reconstructed.angle() * 180 / M_PI << " deg\n";

    return 0;
}
