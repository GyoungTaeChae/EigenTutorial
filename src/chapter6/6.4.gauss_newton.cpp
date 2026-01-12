/**
 * Chapter 6.4: Gauss-Newton Method
 *
 * Topics: Linearization, normal equations, iterative optimization
 * SLAM: Core algorithm in SLAM optimization
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 6.4 Gauss-Newton Method ===\n\n";

    // Gauss-Newton linearizes the residual:
    // r(x + dx) = r(x) + J * dx
    //
    // Normal equations: (J^T J) dx = -J^T r
    // Update: x = x + dx

    // Generate data for fitting y = a*exp(b*x)
    double a_true = 2.0, b_true = 0.5;
    std::vector<double> data_x = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> data_y;
    srand(42);
    for (double xi : data_x) {
        data_y.push_back(a_true * exp(b_true * xi) + 0.1 * ((rand() % 100) / 100.0 - 0.5));
    }

    // Initial guess
    double a_gn = 1.0, b_gn = 1.0;
    int n_data = data_x.size();

    std::cout << "Initial guess: a = " << a_gn << ", b = " << b_gn << "\n\n";

    for (int iter = 0; iter < 10; ++iter) {
        // Compute residuals and Jacobian
        Eigen::VectorXd r(n_data);
        Eigen::MatrixXd J(n_data, 2);

        double cost = 0;
        for (int i = 0; i < n_data; ++i) {
            double xi = data_x[i];
            double yi = data_y[i];
            double pred = a_gn * exp(b_gn * xi);

            r(i) = yi - pred;
            cost += r(i) * r(i);

            // Jacobian: dr/da = -exp(b*x), dr/db = -a*x*exp(b*x)
            J(i, 0) = -exp(b_gn * xi);
            J(i, 1) = -a_gn * xi * exp(b_gn * xi);
        }

        // Gauss-Newton update: (J^T J) dx = -J^T r
        Eigen::Matrix2d H = J.transpose() * J;     // Hessian approximation
        Eigen::Vector2d g = -J.transpose() * r;    // Gradient

        Eigen::Vector2d dx = H.ldlt().solve(g);

        a_gn += dx(0);
        b_gn += dx(1);

        std::cout << "Iter " << iter << ": a = " << a_gn << ", b = " << b_gn
             << ", cost = " << cost << ", |dx| = " << dx.norm() << "\n";

        if (dx.norm() < 1e-8) {
            std::cout << "Converged!\n";
            break;
        }
    }

    return 0;
}
