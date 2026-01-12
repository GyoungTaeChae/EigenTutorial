/**
 * Chapter 5.8: Block Sparse Operations
 *
 * Topics: Working with block matrices in SLAM
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.8 Block Sparse Operations ===\n\n";

    // In SLAM, we often work with block matrices
    // Eigen doesn't have native block-sparse, but we can use dense blocks

    // Store blocks separately and assemble
    Matrix3d block_00 = Matrix3d::Identity() * 10;
    Matrix3d block_11 = Matrix3d::Identity() * 10;
    Matrix3d block_01 = Matrix3d::Ones() * (-1);

    // Assemble into sparse
    typedef Triplet<double> T;
    vector<T> block_trips;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (abs(block_00(i, j)) > 1e-10)
                block_trips.push_back(T(i, j, block_00(i, j)));
            if (abs(block_11(i, j)) > 1e-10)
                block_trips.push_back(T(3 + i, 3 + j, block_11(i, j)));
            if (abs(block_01(i, j)) > 1e-10) {
                block_trips.push_back(T(i, 3 + j, block_01(i, j)));
                block_trips.push_back(T(3 + i, j, block_01(i, j)));  // Symmetric
            }
        }
    }

    SparseMatrix<double> block_sparse(6, 6);
    block_sparse.setFromTriplets(block_trips.begin(), block_trips.end());
    cout << "Block sparse matrix:\n" << MatrixXd(block_sparse) << "\n";

    return 0;
}
