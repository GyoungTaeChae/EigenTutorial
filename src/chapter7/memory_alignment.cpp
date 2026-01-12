/**
 * Chapter 7.1: Memory Alignment
 *
 * Topics: SIMD alignment, aligned_allocator for STL containers
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.1 Memory Alignment ===\n\n";

    // Fixed-size Eigen types with 16-byte alignment requirement:
    // Vector2d, Vector4d, Matrix2d, Matrix4d, Quaterniond, etc.
    // These require special alignment for SIMD operations

    // Problem: STL containers may not align properly
    // Solution 1: Use Eigen's aligned allocator
    vector<Vector4d, aligned_allocator<Vector4d>> aligned_vectors;
    aligned_vectors.push_back(Vector4d(1, 2, 3, 4));
    aligned_vectors.push_back(Vector4d(5, 6, 7, 8));

    cout << "Aligned vector of Vector4d:\n";
    for (const auto& v : aligned_vectors) {
        cout << "  " << v.transpose() << "\n";
    }
    cout << "\n";

    // Solution 2: Use dynamically-sized types (no alignment issues)
    vector<VectorXd> dynamic_vectors;
    dynamic_vectors.push_back(VectorXd::Ones(4));
    cout << "Dynamic vector (no alignment issue): " << dynamic_vectors[0].transpose() << "\n\n";

    // Note: Vector3d does NOT have 16-byte alignment requirement
    vector<Vector3d> vec3_container;
    vec3_container.push_back(Vector3d(1, 2, 3));
    cout << "Vector3d in std::vector: " << vec3_container[0].transpose() << "\n";

    return 0;
}
