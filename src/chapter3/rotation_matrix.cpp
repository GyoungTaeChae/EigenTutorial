/**
 * Chapter 3.1: Rotation Matrix (SO3)
 *
 * Topics: Rotation matrix properties, orthogonality, determinant
 * SLAM: Rotation matrices represent orientation
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.1 Rotation Matrix (SO3) ===\n\n";

    // Properties of rotation matrix R:
    // - R^T * R = I (orthogonal)
    // - det(R) = 1 (proper rotation, not reflection)
    // - R belongs to SO(3): Special Orthogonal group in 3D

    // Create rotation matrix from angle around Z-axis
    double angle_z = M_PI / 4;  // 45 degrees
    Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    cout << "Rotation around Z-axis (45 deg):\n" << Rz << "\n\n";
    cout << "R^T * R (should be I):\n" << Rz.transpose() * Rz << "\n\n";
    cout << "R * R^T (should be I):\n" << Rz * Rz.transpose() << "\n\n";
    cout << "det(R) (should be 1): " << Rz.determinant() << "\n";
    return 0;
}
