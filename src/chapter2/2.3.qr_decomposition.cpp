/**
 * Chapter 2.3: QR Decomposition
 *
 * Topics: A = Q * R, Q orthogonal, R upper triangular
 * SLAM Applications: Least squares, numerical stability, orthogonalization
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 2.3 QR Decomposition ===\n";
    std::cout << "A = Q * R (Q orthogonal, R upper triangular)\n\n";

    Eigen::MatrixXd B(4, 3);
    B << 1, 2, 3,
         4, 5, 6,
         7, 8, 9,
         10, 11, 12;

    Eigen::HouseholderQR<Eigen::MatrixXd> qr(B);
    Eigen::MatrixXd Q_mat = qr.householderQ() * Eigen::MatrixXd::Identity(4, 3);
    Eigen::MatrixXd R_mat = qr.matrixQR().triangularView<Eigen::Upper>().toDenseMatrix().topRows(3);

    std::cout << "Original B:\n" << B << "\n\n";
    std::cout << "Q (orthogonal):\n" << Q_mat << "\n\n";
    std::cout << "R (upper triangular):\n" << R_mat << "\n\n";

    // Verify Q is orthogonal: Q^T * Q = I
    std::cout << "Q^T * Q (should be I):\n" << Q_mat.transpose() * Q_mat << "\n";

    return 0;
}
