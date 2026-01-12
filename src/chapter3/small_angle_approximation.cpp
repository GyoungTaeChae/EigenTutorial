/**
 * Chapter 3.10: Small Angle Approximation
 *
 * Topics: R = I + [w]_x for small rotations
 * Key for Jacobian computation in SLAM optimization
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 3.10 Small Angle Approximation ===\n\n";

    // For small rotations (common in optimization):
    // R = I + [w]_x  where w is the rotation vector
    // This linearization is key for Jacobian computation

    Vector3d small_omega(0.01, 0.02, 0.03);  // Small rotation

    // Skew-symmetric matrix
    Matrix3d omega_skew;
    omega_skew <<  0,           -small_omega.z(),  small_omega.y(),
                   small_omega.z(),  0,           -small_omega.x(),
                  -small_omega.y(),  small_omega.x(),  0;

    // Approximation
    Matrix3d R_approx = Matrix3d::Identity() + omega_skew;

    // Exact (from angle-axis)
    double omega_norm = small_omega.norm();
    AngleAxisd exact_aa(omega_norm, small_omega.normalized());
    // std::cout << "Omega norm: " << omega_norm << std::endl;
    Matrix3d R_exact = exact_aa.toRotationMatrix();

    cout << "Small rotation vector: " << small_omega.transpose() << "\n\n";
    cout << "Approximate R:\n" << R_approx << "\n\n";
    cout << "Exact R:\n" << R_exact << "\n\n";
    cout << "Error norm: " << (R_approx - R_exact).norm() << "\n";

    return 0;
}
