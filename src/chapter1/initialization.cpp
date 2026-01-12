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

    // Random matrix (values between -1 and 1)
    Matrix3d rand_mat = Matrix3d::Random();
    cout << "Random matrix:\n" << rand_mat << "\n\n";

    // Constant matrix
    Matrix3d const_mat = Matrix3d::Constant(3.14);
    cout << "Constant matrix:\n" << const_mat << "\n\n";

    // Comma initialization
    Matrix3d m;
    m << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    cout << "Comma initialized:\n" << m << "\n\n";

    // Vector initialization
    Vector3d v(1.0, 2.0, 3.0);
    cout << "Vector: " << v.transpose() << "\n";

    return 0;
}
