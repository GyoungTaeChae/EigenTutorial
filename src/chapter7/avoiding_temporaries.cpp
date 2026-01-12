/**
 * Chapter 7.3: Avoiding Temporaries
 *
 * Topics: noalias(), aliasing, performance optimization
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.3 Avoiding Temporaries ===\n\n";

    Matrix3d A = Matrix3d::Random();
    Matrix3d B = Matrix3d::Random();
    Matrix3d C;

    // BAD: Aliasing problem - C appears on both sides
    // C = A * C;  // Creates a hidden temporary (safe but slow)

    // GOOD: Use .noalias() when you're sure there's no aliasing
    C = Matrix3d::Random();
    C.noalias() = A * B;  // No temporary, direct write
    cout << "Result with noalias():\n" << C << "\n\n";

    // When to use noalias():
    // - Matrix multiplication where result is different from operands
    // - Performance-critical inner loops
    // DON'T use when:
    // - Result matrix appears in the expression (aliasing)

    cout << "Tips:\n";
    cout << "- Use noalias() for C = A * B when C != A and C != B\n";
    cout << "- Avoids creating temporary matrices\n";
    cout << "- Important in tight loops\n";

    return 0;
}
