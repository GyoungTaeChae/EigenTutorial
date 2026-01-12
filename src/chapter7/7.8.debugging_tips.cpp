/**
 * Chapter 7.8: Debugging Tips
 *
 * Topics: Printing, dimension checks, compile flags
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 7.8 Debugging Tips ===\n\n";

    Eigen::Matrix3d M;
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    std::cout << "1. Use std::cout << mat.format(Eigen::IOFormat(...)) for pretty printing\n\n";

    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    std::cout << "   Example:\n" << M.format(CleanFmt) << "\n\n";

    std::cout << "2. Check matrix sizes with .rows(), .cols(), .size()\n";
    std::cout << "   M is " << M.rows() << "x" << M.cols() << "\n\n";

    std::cout << "3. Use assert() for dimension checks in debug builds\n";
    std::cout << "   assert(A.cols() == B.rows());\n\n";

    std::cout << "4. Compile with -DEIGEN_INITIALIZE_MATRICES_BY_NAN\n";
    std::cout << "   to catch uninitialized data\n\n";

    std::cout << "5. Use Eigen's internal asserts:\n";
    std::cout << "   compile with -DEIGEN_INTERNAL_DEBUGGING\n";

    return 0;
}
