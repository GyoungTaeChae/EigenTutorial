/**
 * Chapter 4.8: Practical - Triangulation
 *
 * Topics: Finding 3D point from multiple camera observations
 * SLAM: Essential for stereo vision and multi-view geometry
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.8 Practical: Triangulation ===\n\n";

    // Given point observations from multiple cameras, find 3D point
    // This is a least squares problem

    // Camera 1: at origin, looking along Z
    // Camera 2: at (1, 0, 0), looking along Z

    // Projection matrices (simplified pinhole)
    Matrix<double, 3, 4> P1, P2;
    P1 << 1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0;

    Matrix3d R2 = Matrix3d::Identity();
    Vector3d t2(1, 0, 0);
    P2 << R2.row(0), -R2.row(0).dot(t2),
          R2.row(1), -R2.row(1).dot(t2),
          R2.row(2), -R2.row(2).dot(t2);

    // True 3D point
    Vector3d point_3d(0.5, 0.5, 2.0);

    // Project to get 2D observations (homogeneous)
    Vector4d point_homo(point_3d.x(), point_3d.y(), point_3d.z(), 1);
    Vector3d obs1 = P1 * point_homo;  obs1 /= obs1(2);
    Vector3d obs2 = P2 * point_homo;  obs2 /= obs2(2);

    cout << "Observation in camera 1: (" << obs1(0) << ", " << obs1(1) << ")\n";
    cout << "Observation in camera 2: (" << obs2(0) << ", " << obs2(1) << ")\n\n";

    // Linear triangulation using DLT
    // Each observation gives 2 equations (from x and y)
    Matrix<double, 4, 4> A_tri;
    A_tri.row(0) = obs1(0) * P1.row(2) - P1.row(0);
    A_tri.row(1) = obs1(1) * P1.row(2) - P1.row(1);
    A_tri.row(2) = obs2(0) * P2.row(2) - P2.row(0);
    A_tri.row(3) = obs2(1) * P2.row(2) - P2.row(1);

    // Solve using SVD (homogeneous system, find null space)
    JacobiSVD<Matrix<double, 4, 4>> svd_tri(A_tri, ComputeFullV);
    Vector4d X_homo = svd_tri.matrixV().col(3);

    // Convert from homogeneous
    Vector3d X_recovered = X_homo.head<3>() / X_homo(3);

    cout << "True 3D point: " << point_3d.transpose() << "\n";
    cout << "Triangulated:  " << X_recovered.transpose() << "\n";
    cout << "Error: " << (X_recovered - point_3d).norm() << "\n";

    return 0;
}
