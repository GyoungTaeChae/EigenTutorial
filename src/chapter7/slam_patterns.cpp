/**
 * Chapter 7.9: SLAM-Specific Patterns
 *
 * Topics: Covariance propagation, information matrices, pose accumulation
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.9 SLAM Patterns ===\n\n";

    // Pattern 1: Covariance propagation
    // If y = f(x) and x has covariance P, then y has covariance J*P*J^T
    Matrix3d P_in = Matrix3d::Identity() * 0.1;  // Input covariance
    Matrix<double, 2, 3> J_func;  // Jacobian of some function
    J_func << 1, 0, 0.5,
              0, 1, 0.3;
    Matrix2d P_out = J_func * P_in * J_func.transpose();
    cout << "Covariance propagation: P_out = J * P_in * J^T\n";
    cout << "P_out:\n" << P_out << "\n\n";

    // Pattern 2: Information (inverse covariance) matrices
    Matrix3d Info = P_in.inverse();
    cout << "Information matrix:\n" << Info << "\n\n";

    // Pattern 3: Efficient pose inverse
    // For SE(3): T^{-1} = [R^T | -R^T * t]
    Isometry3d T = Isometry3d::Identity();
    T.rotate(AngleAxisd(0.5, Vector3d::UnitZ()));
    T.translation() = Vector3d(1, 2, 3);

    Isometry3d T_inv = T.inverse();  // Efficient for Isometry
    cout << "Pose inverse (efficient for Isometry3d):\n";
    cout << "T * T^{-1}:\n" << (T * T_inv).matrix() << "\n\n";

    // Pattern 4: Accumulating transformations
    vector<Isometry3d, aligned_allocator<Isometry3d>> trajectory;
    Isometry3d current_pose = Isometry3d::Identity();
    trajectory.push_back(current_pose);

    // Simulate odometry updates
    for (int i = 0; i < 5; ++i) {
        Isometry3d delta = Isometry3d::Identity();
        delta.translation() = Vector3d(1, 0, 0);  // Move forward
        delta.rotate(AngleAxisd(0.1, Vector3d::UnitZ()));  // Slight turn

        current_pose = current_pose * delta;  // Accumulate
        trajectory.push_back(current_pose);
    }

    cout << "Accumulated trajectory positions:\n";
    for (size_t i = 0; i < trajectory.size(); ++i) {
        cout << "  Pose " << i << ": " << trajectory[i].translation().transpose() << "\n";
    }

    return 0;
}
