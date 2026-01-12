/**
 * Chapter 7.8: Debugging Tips
 *
 * Topics: Printing, dimension checks, compile flags
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.8 Debugging Tips ===\n\n";

    Matrix3d M;
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

    cout << "1. Use cout << mat.format(IOFormat(...)) for pretty printing\n\n";

    IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    cout << "   Example:\n" << M.format(CleanFmt) << "\n\n";

    cout << "2. Check matrix sizes with .rows(), .cols(), .size()\n";
    cout << "   M is " << M.rows() << "x" << M.cols() << "\n\n";

    cout << "3. Use assert() for dimension checks in debug builds\n";
    cout << "   assert(A.cols() == B.rows());\n\n";

    cout << "4. Compile with -DEIGEN_INITIALIZE_MATRICES_BY_NAN\n";
    cout << "   to catch uninitialized data\n\n";

    cout << "5. Use Eigen's internal asserts:\n";
    cout << "   compile with -DEIGEN_INTERNAL_DEBUGGING\n";

    return 0;
}
