/**
 * Chapter 5.7: Practical - Pose Graph Hessian
 *
 * Topics: Structure of pose graph SLAM Hessian matrix
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.7 Practical: Pose Graph Hessian ===\n\n";

    // In pose graph SLAM, the Hessian has a specific structure:
    // - Block diagonal: individual pose uncertainties
    // - Off-diagonal blocks: constraints between poses

    // Simulate 5 poses, each with 3 DOF (2D: x, y, theta)
    int num_poses = 5;
    int pose_dim = 3;
    int total_dim = num_poses * pose_dim;

    typedef Triplet<double> T;
    vector<T> hessian_trips;

    // Diagonal blocks (prior/odometry information)
    for (int i = 0; i < num_poses; ++i) {
        int base = i * pose_dim;
        for (int r = 0; r < pose_dim; ++r) {
            for (int c = 0; c < pose_dim; ++c) {
                double val = (r == c) ? 10.0 : 0.1;
                hessian_trips.push_back(T(base + r, base + c, val));
            }
        }
    }

    // Off-diagonal blocks (loop closures: pose 0 sees pose 3 and 4)
    vector<pair<int, int>> loop_closures = {{0, 3}, {0, 4}};
    for (const auto& lc : loop_closures) {
        int base_i = lc.first * pose_dim;
        int base_j = lc.second * pose_dim;
        for (int r = 0; r < pose_dim; ++r) {
            for (int c = 0; c < pose_dim; ++c) {
                double val = (r == c) ? -2.0 : -0.05;
                hessian_trips.push_back(T(base_i + r, base_j + c, val));
                hessian_trips.push_back(T(base_j + r, base_i + c, val));
                hessian_trips.push_back(T(base_i + r, base_i + c, -val));
                hessian_trips.push_back(T(base_j + r, base_j + c, -val));
            }
        }
    }

    SparseMatrix<double> H(total_dim, total_dim);
    H.setFromTriplets(hessian_trips.begin(), hessian_trips.end());

    cout << "Pose graph Hessian structure (15x15 for 5 poses):\n";
    cout << "Non-zeros: " << H.nonZeros() << " / " << total_dim * total_dim << "\n";
    cout << "Sparsity: " << 100.0 * (1.0 - (double)H.nonZeros() / (total_dim * total_dim)) << "% zeros\n\n";

    // Visualize sparsity pattern
    cout << "Sparsity pattern (* = non-zero):\n";
    MatrixXd H_dense = MatrixXd(H);
    for (int i = 0; i < total_dim; ++i) {
        for (int j = 0; j < total_dim; ++j) {
            cout << (abs(H_dense(i, j)) > 1e-10 ? "*" : ".");
        }
        cout << "\n";
    }

    return 0;
}
