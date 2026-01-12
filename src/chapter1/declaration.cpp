/**
 * Chapter 1.1: Matrix and Vector Declaration
 *
 * Topics: Fixed-size and dynamic-size matrices/vectors
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 1.1 Matrix and Vector Declaration ===\n\n";

    // Fixed-size matrices (compile-time size - faster, stack allocated)
    Matrix3d R;                    // 3x3 double matrix
    Matrix4d T;                    // 4x4 double matrix (transformation)
    Vector3d t;                    // 3x1 double vector (translation)

    // Dynamic-size matrices (runtime size - heap allocated)
    MatrixXd A(3, 4);              // 3x4 double matrix
    VectorXd b(5);                 // 5x1 double vector

    // Common typedefs in SLAM:
    // Matrix3d = Matrix<double, 3, 3>  -> Rotation matrices
    // Vector3d = Matrix<double, 3, 1>  -> 3D points, translations
    // Matrix4d = Matrix<double, 4, 4>  -> Homogeneous transformations
    // MatrixXd = Matrix<double, Dynamic, Dynamic> -> Jacobians, covariances

    cout << "Matrix A size: " << A.rows() << "x" << A.cols() << "\n";
    cout << "Vector b size: " << b.size() << "\n";
    return 0;
}
