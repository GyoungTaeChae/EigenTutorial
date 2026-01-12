/**
 * Chapter 1.6: Element-wise Operations
 *
 * Topics: Array operations, sqrt, square, exp, Hadamard product, min/max/sum/mean
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 1.6 Element-wise Operations ===\n\n";

    Matrix3d M = Matrix3d::Random().cwiseAbs();  // Make positive
    Matrix3d A3 = Matrix3d::Random();
    Matrix3d B3 = Matrix3d::Random();

    // Element-wise operations using .array()
    cout << "Original:\n" << M << "\n\n";
    cout << "Square root:\n" << M.array().sqrt() << "\n\n";
    cout << "Squared:\n" << M.array().square() << "\n\n";
    cout << "Exponential:\n" << M.array().exp() << "\n\n";

    // Element-wise multiplication (Hadamard product)
    Matrix3d hadamard = A3.cwiseProduct(B3);
    cout << "Element-wise product:\n" << hadamard << "\n\n";

    // Min, max, sum, mean
    cout << "Min: " << M.minCoeff() << "\n";
    cout << "Max: " << M.maxCoeff() << "\n";
    cout << "Sum: " << M.sum() << "\n";
    cout << "Mean: " << M.mean() << "\n";

    return 0;
}
