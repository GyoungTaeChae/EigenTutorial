/**
 * Chapter 7.5: Common Pitfalls
 *
 * Topics: Mistakes to avoid when using Eigen
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

int main() {
    std::cout << "=== 7.5 Common Pitfalls ===\n\n";

    // PITFALL 1: Comma initialization with wrong number of elements
    // Matrix3d M;
    // M << 1, 2, 3, 4, 5;  // WRONG! Missing elements
    Eigen::Matrix3d M;
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;  // CORRECT
    std::cout << "Pitfall 1: Always use correct number of elements in comma init\n\n";

    // PITFALL 2: Using .transpose() in place
    // VectorXd v = ...;
    // v = v.transpose();  // May cause issues!
    // Use: v.transposeInPlace();
    std::cout << "Pitfall 2: Use .transposeInPlace() for in-place transpose\n\n";

    // PITFALL 3: Forgetting .matrix() or .array()
    Eigen::VectorXd vec_a = Eigen::VectorXd::LinSpaced(5, 0, 4);
    Eigen::VectorXd vec_b = Eigen::VectorXd::LinSpaced(5, 1, 5);
    // vec_a * vec_b;  // ERROR for vectors
    Eigen::VectorXd elem_mult = vec_a.array() * vec_b.array();  // Element-wise
    std::cout << "Element-wise product: " << elem_mult.transpose() << "\n\n";

    // PITFALL 4: Integer division in expressions
    // Matrix3d M = Matrix3d::Identity() / 2;  // All zeros! (integer division)
    Eigen::Matrix3d M_correct = Eigen::Matrix3d::Identity() / 2.0;  // Correct
    std::cout << "Pitfall 4: Use 2.0 not 2 for division\n\n";

    // PITFALL 5: Quaternion multiplication order
    // q1 * q2 applies q2 first, then q1 (like matrices)
    Eigen::Quaterniond qa(Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d::UnitZ()));
    Eigen::Quaterniond qb(Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d::UnitX()));
    Eigen::Quaterniond qc = qa * qb;  // First rotate by qb, then by qa
    std::cout << "Pitfall 5: q1*q2 means first q2, then q1 (like matrices)\n";

    return 0;
}
