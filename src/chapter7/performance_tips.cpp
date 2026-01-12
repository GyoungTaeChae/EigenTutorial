/**
 * Chapter 7.6: Performance Tips
 *
 * Topics: Fixed vs dynamic size, squaredNorm, benchmarking
 */

#include <iostream>
#include <chrono>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

class Timer {
public:
    void start() { t_start = chrono::high_resolution_clock::now(); }
    double elapsed_ms() {
        auto t_end = chrono::high_resolution_clock::now();
        return chrono::duration<double, milli>(t_end - t_start).count();
    }
private:
    chrono::time_point<chrono::high_resolution_clock> t_start;
};

int main() {
    cout << "=== 7.6 Performance Tips ===\n\n";

    Timer timer;
    int n_iter = 100000;

    // Tip 1: Prefer fixed-size matrices when size is known
    Matrix4d fixed_mat = Matrix4d::Random();
    MatrixXd dynamic_mat = MatrixXd::Random(4, 4);

    timer.start();
    for (int i = 0; i < n_iter; ++i) {
        Matrix4d result_fixed = fixed_mat * fixed_mat;
        (void)result_fixed;
    }
    double time_fixed = timer.elapsed_ms();

    timer.start();
    for (int i = 0; i < n_iter; ++i) {
        MatrixXd result_dyn = dynamic_mat * dynamic_mat;
        (void)result_dyn;
    }
    double time_dynamic = timer.elapsed_ms();

    cout << "Tip 1: Fixed-size vs Dynamic:\n";
    cout << "  Fixed (4x4): " << time_fixed << " ms\n";
    cout << "  Dynamic (4x4): " << time_dynamic << " ms\n\n";

    // Tip 2: Use .squaredNorm() instead of .norm() when possible
    VectorXd large_vec = VectorXd::Random(1000);

    timer.start();
    for (int i = 0; i < n_iter; ++i) {
        double n = large_vec.norm();
        (void)n;
    }
    double time_norm = timer.elapsed_ms();

    timer.start();
    for (int i = 0; i < n_iter; ++i) {
        double sn = large_vec.squaredNorm();
        (void)sn;
    }
    double time_sq_norm = timer.elapsed_ms();

    cout << "Tip 2: norm() vs squaredNorm():\n";
    cout << "  norm(): " << time_norm << " ms\n";
    cout << "  squaredNorm(): " << time_sq_norm << " ms\n";

    return 0;
}
