/**
 * Chapter 1.2: Initialization Methods
 *
 * Topics: Zero, Identity, Random, Constant, Comma initialization
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 1.2 Initialization Methods ===\n\n";

    // Zero matrix
    Eigen::Matrix3d zeros = Eigen::Matrix3d::Zero();
    std::cout << "Zero matrix:\n" << zeros << "\n\n";

    // Identity matrix
    Eigen::Matrix3d eye = Eigen::Matrix3d::Identity();
    std::cout << "Identity matrix:\n" << eye << "\n\n";

    // Ones matrix
    Eigen::Matrix3d ones = Eigen::Matrix3d::Ones();
    std::cout << "Ones matrix:\n" << ones << "\n\n";

    // Comma initialization
    Eigen::Matrix3d m;
    m << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    std::cout << "Comma initialized:\n" << m << "\n\n";

    // Vector initialization
    Eigen::Vector3d v(1.0, 2.0, 3.0);
    std::cout << "Vector: " << v.transpose() << std::endl;

    return 0;
}
