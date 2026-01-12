/**
 * Chapter 2.5: LU Decomposition
 *
 * Topics: A = P * L * U with partial pivoting
 * SLAM Applications: General linear systems, determinant, matrix inverse
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.5 LU Decomposition ===\n";
    std::cout << "A = P * L * U (with partial pivoting)\n\n";

    Eigen::Matrix3d C;
    C << 1, 2, 3,
         4, 5, 6,
         7, 8, 10;  // Changed to make non-singular

    Eigen::PartialPivLU<Eigen::Matrix3d> lu(C);

    std::cout << "Original C:\n" << C << "\n\n";

    // Solve Cx = b
    Eigen::Vector3d b_lu(1, 2, 3);
    Eigen::Vector3d x_lu = lu.solve(b_lu);
    std::cout << "Solution to C * x = b: " << x_lu.transpose() << "\n";
    std::cout << "Verification C * x: " << (C * x_lu).transpose() << "\n\n";

    // Determinant from LU
    std::cout << "Determinant: " << lu.determinant() << "\n";

    return 0;
}
