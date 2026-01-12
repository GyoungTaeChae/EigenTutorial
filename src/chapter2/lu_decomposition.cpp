/**
 * Chapter 2.5: LU Decomposition
 *
 * Topics: A = P * L * U with partial pivoting
 * SLAM Applications: General linear systems, determinant, matrix inverse
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.5 LU Decomposition ===\n";
    cout << "A = P * L * U (with partial pivoting)\n\n";

    Matrix3d C;
    C << 1, 2, 3,
         4, 5, 6,
         7, 8, 10;  // Changed to make non-singular

    PartialPivLU<Matrix3d> lu(C);

    cout << "Original C:\n" << C << "\n\n";

    // Solve Cx = b
    Vector3d b_lu(1, 2, 3);
    Vector3d x_lu = lu.solve(b_lu);
    cout << "Solution to C * x = b: " << x_lu.transpose() << "\n";
    cout << "Verification C * x: " << (C * x_lu).transpose() << "\n\n";

    // Determinant from LU
    cout << "Determinant: " << lu.determinant() << "\n";

    return 0;
}
