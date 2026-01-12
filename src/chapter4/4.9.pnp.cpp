/**
 * Chapter 4.9: Practical - PnP (Perspective-n-Point)
 *
 * Topics: Estimating camera pose from 3D-2D correspondences
 * SLAM: Camera localization, visual odometry
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 4.9 Practical: Linear Pose Estimation ===\n\n";

    // Given 3D points and their 2D projections, estimate camera pose
    // Simplified linear formulation (DLT)

    // Known 3D points in world frame
    std::vector<Eigen::Vector3d> points_world = {
        Eigen::Vector3d(0, 0, 0),
        Eigen::Vector3d(1, 0, 0),
        Eigen::Vector3d(0, 1, 0),
        Eigen::Vector3d(1, 1, 0),
        Eigen::Vector3d(0, 0, 1),
        Eigen::Vector3d(1, 1, 1)
    };

    // Camera pose (ground truth)
    Eigen::Matrix3d R_cam_gt = Eigen::AngleAxisd(0.2, Eigen::Vector3d::UnitY()).toRotationMatrix();
    Eigen::Vector3d t_cam_gt(0, 0, 3);  // Camera 3 units in front

    // Project points
    std::vector<Eigen::Vector2d> points_2d;
    for (const auto& pw : points_world) {
        Eigen::Vector3d pc = R_cam_gt * pw + t_cam_gt;
        points_2d.push_back(Eigen::Vector2d(pc.x() / pc.z(), pc.y() / pc.z()));
    }

    // Build DLT system (simplified version)
    int n = points_world.size();
    Eigen::MatrixXd A_pnp(2 * n, 12);

    for (int i = 0; i < n; ++i) {
        double X = points_world[i].x();
        double Y = points_world[i].y();
        double Z = points_world[i].z();
        double u = points_2d[i].x();
        double v = points_2d[i].y();

        A_pnp.row(2*i) << X, Y, Z, 1, 0, 0, 0, 0, -u*X, -u*Y, -u*Z, -u;
        A_pnp.row(2*i+1) << 0, 0, 0, 0, X, Y, Z, 1, -v*X, -v*Y, -v*Z, -v;
    }

    // Solve using SVD
    Eigen::JacobiSVD<Eigen::MatrixXd> svd_pnp(A_pnp, Eigen::ComputeFullV);
    Eigen::VectorXd p = svd_pnp.matrixV().col(11);

    // Extract R and t from projection matrix
    Eigen::Matrix<double, 3, 4> P_est;
    P_est << p(0), p(1), p(2), p(3),
             p(4), p(5), p(6), p(7),
             p(8), p(9), p(10), p(11);

    // Normalize so that ||r3|| = 1
    double scale = P_est.block<1,3>(2,0).norm();
    P_est /= scale;

    std::cout << "Estimated projection matrix:\n" << P_est << "\n\n";
    std::cout << "(Full PnP requires nonlinear refinement for accurate R,t extraction)\n";

    return 0;
}
