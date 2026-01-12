/**
 * Chapter 7.5: Common Pitfalls
 *
 * Topics: Mistakes to avoid when using Eigen
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.5 Common Pitfalls ===\n\n";

    // PITFALL 1: Comma initialization with wrong number of elements
    // Matrix3d M;
    // M << 1, 2, 3, 4, 5;  // WRONG! Missing elements
    Matrix3d M;
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;  // CORRECT
    cout << "Pitfall 1: Always use correct number of elements in comma init\n\n";

    // PITFALL 2: Using .transpose() in place
    // VectorXd v = ...;
    // v = v.transpose();  // May cause issues!
    // Use: v.transposeInPlace();
    cout << "Pitfall 2: Use .transposeInPlace() for in-place transpose\n\n";

    // PITFALL 3: Forgetting .matrix() or .array()
    VectorXd vec_a = VectorXd::LinSpaced(5, 0, 4);
    VectorXd vec_b = VectorXd::LinSpaced(5, 1, 5);
    // vec_a * vec_b;  // ERROR for vectors
    VectorXd elem_mult = vec_a.array() * vec_b.array();  // Element-wise
    cout << "Element-wise product: " << elem_mult.transpose() << "\n\n";

    // PITFALL 4: Integer division in expressions
    // Matrix3d M = Matrix3d::Identity() / 2;  // All zeros! (integer division)
    Matrix3d M_correct = Matrix3d::Identity() / 2.0;  // Correct
    cout << "Pitfall 4: Use 2.0 not 2 for division\n\n";

    // PITFALL 5: Quaternion multiplication order
    // q1 * q2 applies q2 first, then q1 (like matrices)
    Quaterniond qa(AngleAxisd(M_PI/2, Vector3d::UnitZ()));
    Quaterniond qb(AngleAxisd(M_PI/2, Vector3d::UnitX()));
    Quaterniond qc = qa * qb;  // First rotate by qb, then by qa
    cout << "Pitfall 5: q1*q2 means first q2, then q1 (like matrices)\n";

    return 0;
}
