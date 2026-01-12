/**
 * Chapter 6.9: Simple Bundle Adjustment Problem
 *
 * Topics: Setting up BA problem structure
 * SLAM: Core of visual SLAM backend
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 6.9 Simple BA Problem ===\n\n";

    // Minimal BA: 1 camera, 3 3D points, 3 observations
    // Optimize camera pose and point positions

    // Camera intrinsics
    double fx = 500, fy = 500, cx = 320, cy = 240;

    auto project = [&](const Vector3d& P) -> Vector2d {
        return Vector2d(fx * P.x() / P.z() + cx,
                        fy * P.y() / P.z() + cy);
    };

    // True values
    Matrix3d R_ba_true = AngleAxisd(0.1, Vector3d(1, 0, 0).normalized()).toRotationMatrix();
    Vector3d t_ba_true(0.1, 0.2, 0.0);

    vector<Vector3d> points_true = {
        Vector3d(0, 0, 5),
        Vector3d(1, 0, 5),
        Vector3d(0, 1, 5)
    };

    // Generate observations
    vector<Vector2d> observations;
    for (const auto& pt : points_true) {
        Vector3d pc = R_ba_true * pt + t_ba_true;
        observations.push_back(project(pc));
    }

    cout << "True pose: t = " << t_ba_true.transpose() << "\n";
    cout << "Observations:\n";
    for (size_t i = 0; i < observations.size(); ++i) {
        cout << "  Point " << i << ": " << observations[i].transpose() << "\n";
    }
    cout << "\nThis setup is ready for Gauss-Newton optimization.\n";
    cout << "Full implementation requires libraries like Ceres or g2o.\n";

    return 0;
}
