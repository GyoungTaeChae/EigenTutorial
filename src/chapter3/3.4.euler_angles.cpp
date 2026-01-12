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

int main() {
    std::cout << "=== 3.4 Euler Angles ===\n\n";

    std::cout << "WARNING: Euler angles have gimbal lock!\n";
    std::cout << "Use only for display, not for computation.\n\n";

    // Create rotation matrix
    double angle_z = M_PI / 4;  // 45 degrees
    Eigen::Matrix3d Rz;
    Rz << cos(angle_z), -sin(angle_z), 0,
          sin(angle_z),  cos(angle_z), 0,
          0,             0,            1;

    // Extract Euler angles from rotation matrix
    // Eigen uses intrinsic rotations: ZYX means first rotate around X, then Y, then Z
    Eigen::Vector3d euler = Rz.eulerAngles(2, 1, 0);  // ZYX convention (yaw, pitch, roll)
    std::cout << "Euler angles (ZYX) from Rz:\n";
    std::cout << "  Yaw (Z): " << euler[0] * 180 / M_PI << " deg\n";
    std::cout << "  Pitch (Y): " << euler[1] * 180 / M_PI << " deg\n";
    std::cout << "  Roll (X): " << euler[2] * 180 / M_PI << " deg\n\n";

    // Create rotation from Euler angles
    Eigen::Matrix3d R_euler = (Eigen::AngleAxisd(euler[0], Eigen::Vector3d::UnitZ())
                      * Eigen::AngleAxisd(euler[1], Eigen::Vector3d::UnitY())
                      * Eigen::AngleAxisd(euler[2], Eigen::Vector3d::UnitX())).toRotationMatrix();
    std::cout << "Reconstructed from Euler:\n" << R_euler << "\n";

    return 0;
}
