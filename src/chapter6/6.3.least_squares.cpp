/**
 * Chapter 6.3: Least Squares Problem Formulation
 *
 * Topics: Minimizing sum of squared residuals
 * SLAM: Core optimization objective
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 6.3 Least Squares Formulation ===\n\n";

    // Minimize sum of squared residuals:
    // min_x  sum_i ||r_i(x)||^2  =  min_x ||r(x)||^2
    //
    // Where r(x) is the residual vector
    // In SLAM: r(x) = measurement - prediction(x)

    // Example: Fit y = a*exp(b*x) to noisy data
    // Parameters: x = [a, b]
    // Residual: r_i = y_i - a*exp(b*x_i)

    // Ground truth
    double a_true = 2.0, b_true = 0.5;

    // Generate noisy data
    std::vector<double> data_x = {0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> data_y;
    srand(42);
    for (double xi : data_x) {
        data_y.push_back(a_true * exp(b_true * xi) + 0.1 * ((rand() % 100) / 100.0 - 0.5));
    }

    std::cout << "Fitting y = a * exp(b * x)\n";
    std::cout << "True parameters: a = " << a_true << ", b = " << b_true << "\n\n";
    std::cout << "Data points:\n";
    for (size_t i = 0; i < data_x.size(); ++i) {
        std::cout << "  (" << data_x[i] << ", " << data_y[i] << ")\n";
    }

    return 0;
}
