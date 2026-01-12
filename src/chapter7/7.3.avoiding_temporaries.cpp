/**
 * Chapter 7.3: Avoiding Temporaries
 *
 * Topics: noalias(), aliasing, performance optimization
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 7.3 Avoiding Temporaries ===\n\n";

    Eigen::Matrix3d A = Eigen::Matrix3d::Random();
    Eigen::Matrix3d B = Eigen::Matrix3d::Random();
    Eigen::Matrix3d C;

    // BAD: Aliasing problem - C appears on both sides
    // C = A * C;  // Creates a hidden temporary (safe but slow)

    // GOOD: Use .noalias() when you're sure there's no aliasing
    C = Eigen::Matrix3d::Random();
    C.noalias() = A * B;  // No temporary, direct write
    std::cout << "Result with noalias():\n" << C << "\n\n";

    // When to use noalias():
    // - Matrix multiplication where result is different from operands
    // - Performance-critical inner loops
    // DON'T use when:
    // - Result matrix appears in the expression (aliasing)

    std::cout << "Tips:\n";
    std::cout << "- Use noalias() for C = A * B when C != A and C != B\n";
    std::cout << "- Avoids creating temporary matrices\n";
    std::cout << "- Important in tight loops\n";

    return 0;
}
