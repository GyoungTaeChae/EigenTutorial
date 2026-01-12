/**
 * Chapter 6.1: Jacobians - The Key to Optimization
 *
 * Topics: Partial derivatives, Jacobian matrix definition
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 6.1 Jacobians ===\n\n";

    // Jacobian J is the matrix of partial derivatives
    // For f: R^n -> R^m, J is m x n
    // J_ij = df_i / dx_j

    // Example: f(x, y) = [x^2 + y, xy, sin(x)]^T
    // J = [2x, 1]
    //     [y,  x]
    //     [cos(x), 0]

    double x_val = 1.0, y_val = 2.0;

    Eigen::Matrix<double, 3, 2> J_example;
    J_example << 2 * x_val, 1,
                 y_val, x_val,
                 cos(x_val), 0;

    std::cout << "Function f(x,y) = [x^2 + y, xy, sin(x)]\n";
    std::cout << "At (x,y) = (1, 2):\n";
    std::cout << "Jacobian:\n" << J_example << "\n";

    return 0;
}
