/**
 * Chapter 1.4: Vector Operations
 *
 * Topics: Dot product, cross product, norm, normalization
 * Important for SLAM: distances, rotation axes, normal vectors
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 1.4 Vector Operations ===\n\n";

    Eigen::Vector3d a(1, 2, 3);
    Eigen::Vector3d b(4, 5, 6);
    Eigen::Vector3d v3(1, 2, 3);

    // Dot product
    double dot = a.dot(b);
    std::cout << "Dot product a.b: " << dot << "\n";

    // Cross product (SLAM: rotation axis, normal vectors)
    Eigen::Vector3d cross = a.cross(b);
    std::cout << "Cross product a x b: " << cross.transpose() << "\n";

    // Norm (SLAM: distances, normalization)
    double norm = v3.norm();
    std::cout << "Norm of (1,2,3): " << norm << "\n";

    // Normalize
    Eigen::Vector3d normalized = v3.normalized();
    std::cout << "Normalized: " << normalized.transpose() << "\n";

    return 0;
}
