/**
 * Chapter 4.6: Multiple Right-Hand Sides
 *
 * Topics: Solving AX = B where B has multiple columns
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.6 Multiple Right-Hand Sides ===\n\n";

    // Solve AX = B where B has multiple columns
    Matrix3d A_multi;
    A_multi << 1, 2, 3,
               4, 5, 6,
               7, 8, 10;

    Matrix<double, 3, 2> B_multi;
    B_multi << 1, 2,
               3, 4,
               5, 6;

    // Factorize once, solve multiple times
    PartialPivLU<Matrix3d> lu_decomp(A_multi);
    Matrix<double, 3, 2> X_multi = lu_decomp.solve(B_multi);

    cout << "Solution X:\n" << X_multi << "\n\n";
    cout << "Verification AX - B:\n" << (A_multi * X_multi - B_multi) << "\n";

    return 0;
}
