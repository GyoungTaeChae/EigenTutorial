/**
 * Chapter 1.6: Element-wise Operations
 *
 * Topics: Array operations, sqrt, square, exp, Hadamard product, min/max/sum/mean
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 1.6 Element-wise Operations ===\n\n";

    Eigen::Matrix3d M = Eigen::Matrix3d::Random().cwiseAbs();  // Make positive
    Eigen::Matrix3d A3 = Eigen::Matrix3d::Random();
    Eigen::Matrix3d B3 = Eigen::Matrix3d::Random();

    // Element-wise operations using .array()
    std::cout << "Original:\n" << M << "\n\n";
    std::cout << "A3:\n" << A3 << "\n\n";
    std::cout << "B3:\n" << B3 << "\n\n";
    std::cout << "Square root:\n" << M.array().sqrt() << "\n\n";
    std::cout << "Squared:\n" << M.array().square() << "\n\n";
    std::cout << "Exponential:\n" << M.array().exp() << "\n\n";

    // Element-wise multiplication (Hadamard product)
    Eigen::Matrix3d hadamard = A3.cwiseProduct(B3);
    std::cout << "Element-wise product:\n" << hadamard << "\n\n";

    // Min, max, sum, mean // 전체 원소에 대한 연산
    std::cout << "Min: " << M.minCoeff() << "\n";
    std::cout << "Max: " << M.maxCoeff() << "\n";
    std::cout << "Sum: " << M.sum() << "\n";
    std::cout << "Mean: " << M.mean() << "\n";

    return 0;
}
