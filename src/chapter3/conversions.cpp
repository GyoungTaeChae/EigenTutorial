/**
 * Chapter 3.7: Conversions Between Representations
 *
 * Topics: Converting between rotation matrix, quaternion, angle-axis, rotation vector
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.7 Conversions Between Representations ===\n\n";

    // Original rotation
    double theta = M_PI / 6;  // 30 degrees around Z
    AngleAxisd original(theta, Vector3d::UnitZ());

    // To all representations
    Matrix3d as_matrix = original.toRotationMatrix();
    Quaterniond as_quat(original);
    Vector3d as_rotvec = original.angle() * original.axis();

    cout << "Original: " << theta * 180 / M_PI << " deg around Z\n\n";
    cout << "As matrix:\n" << as_matrix << "\n\n";
    cout << "As quaternion (x,y,z,w): " << as_quat.coeffs().transpose() << "\n\n";
    cout << "As rotation vector: " << as_rotvec.transpose() << "\n\n";

    // From quaternion to others
    Matrix3d mat_from_quat = as_quat.toRotationMatrix();
    AngleAxisd aa_from_quat(as_quat);

    // From matrix to others
    Quaterniond quat_from_mat(as_matrix);
    AngleAxisd aa_from_mat(as_matrix);

    cout << "All conversions consistent: "
         << ((mat_from_quat - as_matrix).norm() < 1e-10 ? "YES" : "NO") << "\n";

    return 0;
}
