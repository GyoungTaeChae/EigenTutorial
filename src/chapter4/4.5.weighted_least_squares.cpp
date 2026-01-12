/**
 * Chapter 4.5: Weighted Least Squares
 *
 * Topics: Minimize (Ax - b)^T W (Ax - b), handling outliers
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.5 Weighted Least Squares ===\n\n";

    // Minimize (Ax - b)^T W (Ax - b) where W is weight matrix
    // Solution: (A^T W A) x = A^T W b

    // Example: Some measurements are more reliable than others
    Eigen::MatrixXd A_wls(4, 2);
    A_wls << 1, 0,
             1, 1,
             1, 2,
             1, 3;

    Eigen::VectorXd b_wls(4);
    b_wls << 0.1, 2.1, 3.9, 100.0;  // Last point is outlier

    // Weights: low weight for outlier
    Eigen::VectorXd weights(4);
    weights << 1, 1, 1, 0.01;  // Downweight the outlier

    // W is diagonal matrix with weights
    Eigen::MatrixXd W = weights.asDiagonal();

    // Weighted normal equations
    Eigen::MatrixXd AtWA = A_wls.transpose() * W * A_wls;
    Eigen::VectorXd AtWb = A_wls.transpose() * W * b_wls;
    Eigen::Vector2d x_wls = AtWA.ldlt().solve(AtWb);

    // Compare with unweighted
    Eigen::Vector2d x_unwls = A_wls.colPivHouseholderQr().solve(b_wls);

    std::cout << "Points with outlier: (0,0.1), (1,2.1), (2,3.9), (3,100.0)\n";
    std::cout << "Unweighted: y = " << x_unwls(1) << "x + " << x_unwls(0) << "\n";
    std::cout << "Weighted:   y = " << x_wls(1) << "x + " << x_wls(0) << "\n";

    return 0;
}
