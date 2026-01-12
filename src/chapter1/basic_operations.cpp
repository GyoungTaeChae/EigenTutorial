/**
 * Chapter 1.3: Basic Operations
 *
 * Topics: Addition, subtraction, multiplication, transpose, inverse,
 * determinant
 */

#include <Eigen/Dense>
#include <iostream>


int main() {
  std::cout << "=== 1.3 Basic Operations ===\n\n";

  Eigen::Matrix3d A;
  A << 1,2,3,
       4,5,6,
       7,8,9;

  Eigen::Matrix3d B;
  B << 1,2,3,
       4,5,6,
       7,8,9;

  Eigen::Vector3d V1;
  V1 << 1, 2, 3;
  

  std::cout << "A + B = \n" << A+B << "\n\n";
  std::cout << "A - B = \n" << A - B << "\n\n";
  std::cout << "2 * A = \n" << 2.0 * A << "\n\n";
  std::cout << "A / 2 = \n" << A / 2.0 << "\n\n";
  std::cout << "A * B = \n" << A * B << "\n\n";
  std::cout << "A * V1 = \n" << A * V1 << "\n\n";
  std::cout << "A^T = \n" << A.transpose() << "\n\n";
  std::cout << "trace(A) = " << A.trace() << "\n\n";
  std::cout << "A^-1 = \n" << A.inverse() << "\n\n";
  std::cout << "|A| = " << A.determinant() << "\n\n";
  
  return 0;
}

