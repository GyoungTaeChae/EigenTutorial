/**
 * Chapter 6.5: Levenberg-Marquardt Method
 *
 * Topics: Damped optimization, adaptive lambda
 * More robust than pure Gauss-Newton
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 6.5 Levenberg-Marquardt Method ===\n\n";

    // LM adds damping for robustness:
    // (J^T J + lambda * I) dx = -J^T r
    //
    // lambda large -> gradient descent (safe but slow)
    // lambda small -> Gauss-Newton (fast but may diverge)

    // Generate data
    double a_true = 2.0, b_true = 0.5;
    std::vector<double> data_x = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> data_y;
    srand(42);
    for (double xi : data_x) {
        data_y.push_back(a_true * exp(b_true * xi) + 0.1 * ((rand() % 100) / 100.0 - 0.5));
    }

    double a_gn = 1.0, b_gn = 1.0;
    double lambda = 0.01;  // Initial damping
    int n_data = data_x.size();

    std::cout << "Initial guess: a = " << a_gn << ", b = " << b_gn << "\n\n";

    for (int iter = 0; iter < 20; ++iter) {
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

            J(i, 0) = -exp(b_gn * xi);
            J(i, 1) = -a_gn * xi * exp(b_gn * xi);
        }

        // LM update
        Eigen::Matrix2d H = J.transpose() * J;
        Eigen::Vector2d g = -J.transpose() * r;

        // Add damping
        Eigen::Matrix2d H_damped = H + lambda * Eigen::Matrix2d::Identity();
        Eigen::Vector2d dx = H_damped.ldlt().solve(g);

        // Try update
        double a_new = a_gn + dx(0);
        double b_new = b_gn + dx(1);

        // Compute new cost
        double new_cost = 0;
        for (int i = 0; i < n_data; ++i) {
            double pred = a_new * exp(b_new * data_x[i]);
            double ri = data_y[i] - pred;
            new_cost += ri * ri;
        }

        if (new_cost < cost) {
            // Accept update, decrease damping
            a_gn = a_new;
            b_gn = b_new;
            lambda /= 2;
            std::cout << "Iter " << iter << ": ACCEPT, a = " << a_gn << ", b = " << b_gn
                 << ", cost = " << new_cost << ", lambda = " << lambda << "\n";

            if (abs(cost - new_cost) < 1e-10) {
                std::cout << "Converged!\n";
                break;
            }
        } else {
            // Reject update, increase damping
            lambda *= 2;
            std::cout << "Iter " << iter << ": REJECT, increasing lambda to " << lambda << "\n";
        }
    }

    return 0;
}
