/**
 * Chapter 7.4: Expression Templates - Lazy Evaluation
 *
 * Topics: How Eigen fuses operations, .eval()
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 7.4 Expression Templates ===\n\n";

    // Eigen uses expression templates for lazy evaluation
    // Operations are fused and evaluated only when needed

    Eigen::Vector3d v1(1, 2, 3);
    Eigen::Vector3d v2(4, 5, 6);
    Eigen::Vector3d v3(7, 8, 9);

    // This is efficiently computed as single loop (no temporaries)
    Eigen::Vector3d result = 2 * v1 + v2 - 0.5 * v3;
    std::cout << "Fused expression result: " << result.transpose() << "\n\n";

    // Use .eval() to force evaluation when needed
    auto expr = 2 * v1 + v2;  // This is still an expression, not evaluated
    Eigen::Vector3d evaluated = expr.eval();  // Now it's evaluated
    std::cout << "Evaluated expression: " << evaluated.transpose() << "\n\n";

    std::cout << "Benefits of expression templates:\n";
    std::cout << "- Operations are fused into single loops\n";
    std::cout << "- No intermediate temporaries allocated\n";
    std::cout << "- Better cache efficiency\n";

    return 0;
}
