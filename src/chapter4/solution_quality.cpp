/**
 * Chapter 4.7: Solution Quality
 *
 * Topics: Condition number, numerical stability
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 4.7 Solution Quality ===\n\n";

    // Condition number: ratio of largest to smallest singular value
    // High condition number = ill-conditioned = numerical instability

    Matrix3d well_cond;
    well_cond << 1, 0, 0,
                 0, 1, 0,
                 0, 0, 1;

    Matrix3d ill_cond;
    ill_cond << 1, 1, 1,
                1, 1, 1.0001,
                1, 1.0001, 1;

    JacobiSVD<Matrix3d> svd_well(well_cond);
    JacobiSVD<Matrix3d> svd_ill(ill_cond);

    auto sv_well = svd_well.singularValues();
    auto sv_ill = svd_ill.singularValues();

    cout << "Well-conditioned matrix:\n" << well_cond << "\n";
    cout << "Singular values: " << sv_well.transpose() << "\n";
    cout << "Condition number: " << sv_well(0) / sv_well(2) << "\n\n";

    cout << "Ill-conditioned matrix:\n" << ill_cond << "\n";
    cout << "Singular values: " << sv_ill.transpose() << "\n";
    cout << "Condition number: " << sv_ill(0) / sv_ill(2) << "\n";

    return 0;
}
