/**
 * Chapter 4.7: Solution Quality
 *
 * Topics: Condition number, numerical stability
 */

#include <iostream>
#include <cmath>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 4.7 Solution Quality ===\n\n";

    // Condition number: ratio of largest to smallest singular value
    // High condition number = ill-conditioned = numerical instability

    Eigen::Matrix3d well_cond;
    well_cond << 1, 0, 0,
                 0, 1, 0,
                 0, 0, 1;

    Eigen::Matrix3d ill_cond;
    ill_cond << 1, 1, 1,
                1, 1, 1.0001,
                1, 1.0001, 1;

    Eigen::JacobiSVD<Eigen::Matrix3d> svd_well(well_cond);
    Eigen::JacobiSVD<Eigen::Matrix3d> svd_ill(ill_cond);

    auto sv_well = svd_well.singularValues();
    auto sv_ill = svd_ill.singularValues();

    std::cout << "Well-conditioned matrix:\n" << well_cond << "\n";
    std::cout << "Singular values: " << sv_well.transpose() << "\n";
    std::cout << "Condition number: " << sv_well(0) / sv_well(2) << "\n\n";

    std::cout << "Ill-conditioned matrix:\n" << ill_cond << "\n";
    std::cout << "Singular values: " << sv_ill.transpose() << "\n";
    std::cout << "Condition number: " << sv_ill(0) / sv_ill(2) << "\n";

    return 0;
}
