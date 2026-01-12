/**
 * Chapter 7.7: Integration with Other Libraries
 *
 * Topics: OpenCV, ROS integration patterns
 */

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 7.7 Integration Patterns ===\n\n";

    // Converting from OpenCV cv::Mat to Eigen (conceptual)
    // cv::Mat cv_mat = ...;
    // Map<Matrix<double, Dynamic, Dynamic, RowMajor>> eigen_mat(
    //     cv_mat.ptr<double>(), cv_mat.rows, cv_mat.cols);

    // Converting from Eigen to OpenCV (conceptual)
    // Matrix3d eigen_mat = ...;
    // cv::Mat cv_mat(3, 3, CV_64F, eigen_mat.data());

    cout << "OpenCV integration:\n";
    cout << "  Eigen -> CV: cv::Mat(rows, cols, CV_64F, eigen_mat.data())\n";
    cout << "  CV -> Eigen: Map<MatrixXd>(cv_mat.ptr<double>(), rows, cols)\n\n";

    // ROS geometry_msgs integration (conceptual)
    cout << "ROS integration:\n";
    cout << "  tf2::toMsg(Eigen::Isometry3d) -> geometry_msgs::Pose\n";
    cout << "  tf2::fromMsg(geometry_msgs::Pose) -> Eigen::Isometry3d\n\n";

    cout << "Key points:\n";
    cout << "- OpenCV uses row-major, Eigen uses column-major by default\n";
    cout << "- Use Map to avoid copying data\n";
    cout << "- Be careful with data ownership\n";

    return 0;
}
