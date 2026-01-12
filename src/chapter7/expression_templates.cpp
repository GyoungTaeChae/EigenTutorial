/**
 * Chapter 7.4: Expression Templates - Lazy Evaluation
 *
 * Topics: How Eigen fuses operations, .eval()
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.4 Expression Templates ===\n\n";

    // Eigen uses expression templates for lazy evaluation
    // Operations are fused and evaluated only when needed

    Vector3d v1(1, 2, 3);
    Vector3d v2(4, 5, 6);
    Vector3d v3(7, 8, 9);

    // This is efficiently computed as single loop (no temporaries)
    Vector3d result = 2 * v1 + v2 - 0.5 * v3;
    cout << "Fused expression result: " << result.transpose() << "\n\n";

    // Use .eval() to force evaluation when needed
    auto expr = 2 * v1 + v2;  // This is still an expression, not evaluated
    Vector3d evaluated = expr.eval();  // Now it's evaluated
    cout << "Evaluated expression: " << evaluated.transpose() << "\n\n";

    cout << "Benefits of expression templates:\n";
    cout << "- Operations are fused into single loops\n";
    cout << "- No intermediate temporaries allocated\n";
    cout << "- Better cache efficiency\n";

    return 0;
}
