/**
 * Chapter 6.2: Numerical Jacobian
 *
 * Topics: Finite differences for Jacobian verification
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

Eigen::Vector3d f_example(double x, double y) {
    return Eigen::Vector3d(x*x + y, x*y, sin(x));
}

int main() {
    std::cout << "=== 6.2 Numerical Jacobian ===\n\n";

    // Use finite differences to approximate Jacobian
    // J_ij = (f_i(x + eps*e_j) - f_i(x - eps*e_j)) / (2*eps)

    double x_val = 1.0, y_val = 2.0;

    // Analytical Jacobian
    Eigen::Matrix<double, 3, 2> J_analytical;
    J_analytical << 2 * x_val, 1,
                    y_val, x_val,
                    cos(x_val), 0;

    double eps = 1e-6;
    Eigen::Matrix<double, 3, 2> J_numerical;

    // Partial w.r.t. x
    Eigen::Vector3d f_plus_x = f_example(x_val + eps, y_val);
    Eigen::Vector3d f_minus_x = f_example(x_val - eps, y_val);
    J_numerical.col(0) = (f_plus_x - f_minus_x) / (2 * eps);

    // Partial w.r.t. y
    Eigen::Vector3d f_plus_y = f_example(x_val, y_val + eps);
    Eigen::Vector3d f_minus_y = f_example(x_val, y_val - eps);
    J_numerical.col(1) = (f_plus_y - f_minus_y) / (2 * eps);

    std::cout << "Analytical Jacobian:\n" << J_analytical << "\n\n";
    std::cout << "Numerical Jacobian:\n" << J_numerical << "\n\n";
    std::cout << "Error vs analytical: " << (J_numerical - J_analytical).norm() << "\n";

    return 0;
}
