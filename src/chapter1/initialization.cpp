/**
 * Chapter 1.2: Initialization Methods
 *
 * Topics: Zero, Identity, Random, Constant, Comma initialization
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 1.2 Initialization Methods ===\n\n";

    // Zero matrix
    Matrix3d zeros = Matrix3d::Zero();
    cout << "Zero matrix:\n" << zeros << "\n\n";

    // Identity matrix
    Matrix3d eye = Matrix3d::Identity();
    cout << "Identity matrix:\n" << eye << "\n\n";

    // Ones matrix
    Matrix3d ones = Matrix3d::Ones();
    cout << "Ones matrix:\n" << ones << "\n\n";

    // Comma initialization
    Matrix3d m;
    m << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    cout << "Comma initialized:\n" << m << "\n\n";

    // Vector initialization
    Vector3d v(1.0, 2.0, 3.0);
    cout << "Vector: " << v.transpose() << std::endl;

    return 0;
}
