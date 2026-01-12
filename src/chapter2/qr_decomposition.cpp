/**
 * Chapter 2.3: QR Decomposition
 *
 * Topics: A = Q * R, Q orthogonal, R upper triangular
 * SLAM Applications: Least squares, numerical stability, orthogonalization
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 2.3 QR Decomposition ===\n";
    cout << "A = Q * R (Q orthogonal, R upper triangular)\n\n";

    MatrixXd B(4, 3);
    B << 1, 2, 3,
         4, 5, 6,
         7, 8, 9,
         10, 11, 12;

    HouseholderQR<MatrixXd> qr(B);
    MatrixXd Q_mat = qr.householderQ() * MatrixXd::Identity(4, 3);
    MatrixXd R_mat = qr.matrixQR().triangularView<Upper>().toDenseMatrix().topRows(3);

    cout << "Original B:\n" << B << "\n\n";
    cout << "Q (orthogonal):\n" << Q_mat << "\n\n";
    cout << "R (upper triangular):\n" << R_mat << "\n\n";

    // Verify Q is orthogonal: Q^T * Q = I
    cout << "Q^T * Q (should be I):\n" << Q_mat.transpose() * Q_mat << "\n";

    return 0;
}
