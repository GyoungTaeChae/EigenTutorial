/**
 * Chapter 1.1: Matrix and Vector Declaration
 *
 * Topics: Fixed-size and dynamic-size matrices/vectors
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 1.1 Matrix and Vector Declaration ===\n\n";

    // Fixed-size matrices (compile-time size - faster, stack allocated)
    Eigen::Matrix3d R;                    // 3x3 double matrix
    Eigen::Matrix4d T;                    // 4x4 double matrix (transformation)
    Eigen::Vector3d t;                    // 3x1 double vector (translation)

    // Dynamic-size matrices (runtime size - heap allocated)
    Eigen::MatrixXd A(3, 4);              // 3x4 double matrix
    Eigen::VectorXd b(5);                 // 5x1 double vector

    // Common typedefs in SLAM:
    // Matrix3d = Matrix<double, 3, 3>  -> Rotation matrices
    // Vector3d = Matrix<double, 3, 1>  -> 3D points, translations
    // Matrix4d = Matrix<double, 4, 4>  -> Homogeneous transformations
    // MatrixXd = Matrix<double, Dynamic, Dynamic> -> Jacobians, covariances

    std::cout << "Matrix A size: " << A.rows() << "x" << A.cols() << "\n";
    std::cout << "Vector b size: " << b.size() << "\n";
    return 0;
}
