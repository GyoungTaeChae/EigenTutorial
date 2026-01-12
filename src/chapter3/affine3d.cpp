/**
 * Chapter 3.6: Affine3d
 *
 * Topics: Affine transformations including scaling
 * Use when you need scale, shear, etc.
 */

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.6 Affine3d ===\n\n";

    // Affine transformations include scaling (not just rigid body)

    Affine3d A = Affine3d::Identity();
    A.linear() = 2.0 * Matrix3d::Identity();  // Uniform scale by 2
    A.translation() = Vector3d(1, 1, 1);

    cout << "Affine (scale + translate):\n" << A.matrix() << "\n\n";

    Vector3d point(1, 0, 0);
    Vector3d scaled_point = A * point;
    cout << "Original point: " << point.transpose() << "\n";
    cout << "Scaled point: " << scaled_point.transpose() << "\n";

    return 0;
}
