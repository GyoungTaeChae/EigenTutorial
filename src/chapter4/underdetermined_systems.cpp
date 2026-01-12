/**
 * Chapter 4.4: Underdetermined Systems
 *
 * Topics: Minimum norm solution using SVD
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.4 Underdetermined Systems ===\n\n";

    // More unknowns than equations: infinite solutions
    // Find minimum norm solution

    MatrixXd A_under(2, 4);  // 2 equations, 4 unknowns
    A_under << 1, 2, 3, 4,
               5, 6, 7, 8;

    VectorXd b_under(2);
    b_under << 1, 2;

    // Use SVD for minimum norm solution
    VectorXd x_under = A_under.bdcSvd(ComputeThinU | ComputeThinV).solve(b_under);
    cout << "Minimum norm solution: " << x_under.transpose() << "\n";
    cout << "Solution norm: " << x_under.norm() << "\n";
    cout << "Ax - b: " << (A_under * x_under - b_under).transpose() << "\n";

    return 0;
}
