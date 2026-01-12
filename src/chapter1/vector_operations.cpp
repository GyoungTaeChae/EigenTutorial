/**
 * Chapter 1.4: Vector Operations
 *
 * Topics: Dot product, cross product, norm, normalization
 * Important for SLAM: distances, rotation axes, normal vectors
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 1.4 Vector Operations ===\n\n";

    Vector3d a(1, 2, 3);
    Vector3d b(4, 5, 6);
    Vector3d v3(1, 2, 3);

    // Dot product
    double dot = a.dot(b);
    cout << "Dot product a.b: " << dot << "\n";

    // Cross product (SLAM: rotation axis, normal vectors)
    Vector3d cross = a.cross(b);
    cout << "Cross product a x b: " << cross.transpose() << "\n";

    // Norm (SLAM: distances, normalization)
    double norm = v3.norm();
    cout << "Norm of (1,2,3): " << norm << "\n";

    // Normalize
    Vector3d normalized = v3.normalized();
    cout << "Normalized: " << normalized.transpose() << "\n";

    return 0;
}
