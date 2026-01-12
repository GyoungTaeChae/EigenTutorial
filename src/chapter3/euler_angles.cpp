/**
 * Chapter 3.4: Euler Angles
 *
 * WARNING: Euler angles have gimbal lock and convention ambiguity
 * Use only for human-readable output, NOT for computation
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.4 Euler Angles ===\n\n";

    cout << "WARNING: Euler angles have gimbal lock!\n";
    cout << "Use only for display, not for computation.\n\n";

    // Create rotation matrix
    double angle_z = M_PI / 4;  // 45 degrees
    Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    // Extract Euler angles from rotation matrix
    // Eigen uses intrinsic rotations: ZYX means first rotate around X, then Y, then Z
    Vector3d euler = Rz.eulerAngles(2, 1, 0);  // ZYX convention (yaw, pitch, roll)
    cout << "Euler angles (ZYX) from Rz:\n";
    cout << "  Yaw (Z): " << euler[0] * 180 / M_PI << " deg\n";
    cout << "  Pitch (Y): " << euler[1] * 180 / M_PI << " deg\n";
    cout << "  Roll (X): " << euler[2] * 180 / M_PI << " deg\n\n";

    // Create rotation from Euler angles
    Matrix3d R_euler = (AngleAxisd(euler[0], Vector3d::UnitZ())
                      * AngleAxisd(euler[1], Vector3d::UnitY())
                      * AngleAxisd(euler[2], Vector3d::UnitX())).toRotationMatrix();
    cout << "Reconstructed from Euler:\n" << R_euler << "\n";

    return 0;
}
