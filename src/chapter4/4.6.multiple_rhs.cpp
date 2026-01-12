/**
 * Chapter 4.6: Multiple Right-Hand Sides
 *
 * Topics: Solving AX = B where B has multiple columns
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.6 Multiple Right-Hand Sides ===\n\n";

    // Solve AX = B where B has multiple columns
    Eigen::Matrix3d A_multi;
    A_multi << 1, 2, 3,
               4, 5, 6,
               7, 8, 10;

    Eigen::Matrix<double, 3, 2> B_multi;
    B_multi << 1, 2,
               3, 4,
               5, 6;

    // Factorize once, solve multiple times
    Eigen::PartialPivLU<Eigen::Matrix3d> lu_decomp(A_multi);
    Eigen::Matrix<double, 3, 2> X_multi = lu_decomp.solve(B_multi);

    std::cout << "Solution X:\n" << X_multi << "\n\n";
    std::cout << "Verification AX - B:\n" << (A_multi * X_multi - B_multi) << "\n";

    return 0;
}
