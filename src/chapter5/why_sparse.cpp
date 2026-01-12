/**
 * Chapter 5.1: Why Sparse Matrices?
 *
 * Topics: Memory and computation savings
 * SLAM: Large-scale bundle adjustment, pose graphs
 */

#include <iostream>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.1 Why Sparse Matrices? ===\n\n";

    // In SLAM, we often have large matrices that are mostly zeros
    // Example: 1000 poses, each pose has 6 parameters = 6000 unknowns
    // The Hessian/Information matrix is 6000x6000 = 36 million entries
    // But each pose only connects to a few other poses (sparse)

    int n = 1000;
    double dense_storage = n * n * 8.0 / (1024 * 1024);  // MB
    double sparse_storage = n * 10 * 8.0 / (1024 * 1024); // ~10 non-zeros per row
    cout << "1000x1000 matrix:\n";
    cout << "  Dense storage: " << dense_storage << " MB\n";
    cout << "  Sparse storage (~1% fill): " << sparse_storage << " MB\n";

    return 0;
}
