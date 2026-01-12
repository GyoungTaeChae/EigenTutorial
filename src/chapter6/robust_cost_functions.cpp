/**
 * Chapter 6.8: Robust Cost Functions
 *
 * Topics: Huber, Cauchy kernels for handling outliers
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    cout << "=== 6.8 Robust Cost Functions ===\n\n";

    // Standard least squares: cost = sum(r_i^2)
    // Problem: outliers dominate the cost

    // Robust kernels reduce influence of large residuals:
    // - Huber: quadratic for small r, linear for large r
    // - Cauchy: log(1 + r^2)
    // - Tukey: completely rejects large outliers

    auto huber = [](double r, double delta) -> double {
        double abs_r = abs(r);
        if (abs_r <= delta) {
            return 0.5 * r * r;
        } else {
            return delta * (abs_r - 0.5 * delta);
        }
    };

    auto cauchy = [](double r, double c) -> double {
        return c * c * log(1 + (r/c) * (r/c)) / 2;
    };

    cout << "Residual |  Squared  |  Huber(1) |  Cauchy(1)\n";
    cout << "---------|-----------|-----------|------------\n";
    vector<double> test_residuals = {0.1, 0.5, 1.0, 2.0, 5.0, 10.0};
    for (double r : test_residuals) {
        printf("  %5.1f  |  %7.2f  |  %7.2f  |  %7.2f\n",
               r, 0.5*r*r, huber(r, 1.0), cauchy(r, 1.0));
    }
    cout << "\nNote: Robust kernels grow slower than squared for large residuals\n";
    cout << "This reduces the influence of outliers in optimization.\n";

    return 0;
}
