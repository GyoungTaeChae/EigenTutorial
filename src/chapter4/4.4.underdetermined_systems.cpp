/**
 * Chapter 4.4: Underdetermined Systems
 *
 * Topics: Minimum norm solution using SVD
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.4 Underdetermined Systems ===\n\n";

    // More unknowns than equations: infinite solutions
    // Find minimum norm solution

    Eigen::MatrixXd A_under(2, 4);  // 2 equations, 4 unknowns
    A_under << 1, 2, 3, 4,
               5, 6, 7, 8;

    Eigen::VectorXd b_under(2);
    b_under << 1, 2;

    // Use SVD for minimum norm solution
    Eigen::VectorXd x_under = A_under.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b_under);
    std::cout << "Minimum norm solution: " << x_under.transpose() << "\n";
    std::cout << "Solution norm: " << x_under.norm() << "\n";
    std::cout << "Ax - b: " << (A_under * x_under - b_under).transpose() << "\n";

    return 0;
}
