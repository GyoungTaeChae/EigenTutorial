/**
 * Chapter 7.7: Integration with Other Libraries
 *
 * Topics: OpenCV, ROS integration patterns
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 7.7 Integration Patterns ===\n\n";

    // Converting from OpenCV cv::Mat to Eigen (conceptual)
    // cv::Mat cv_mat = ...;
    // Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> eigen_mat(
    //     cv_mat.ptr<double>(), cv_mat.rows, cv_mat.cols);

    // Converting from Eigen to OpenCV (conceptual)
    // Eigen::Matrix3d eigen_mat = ...;
    // cv::Mat cv_mat(3, 3, CV_64F, eigen_mat.data());

    std::cout << "OpenCV integration:\n";
    std::cout << "  Eigen -> CV: cv::Mat(rows, cols, CV_64F, eigen_mat.data())\n";
    std::cout << "  CV -> Eigen: Eigen::Map<Eigen::MatrixXd>(cv_mat.ptr<double>(), rows, cols)\n\n";

    // ROS geometry_msgs integration (conceptual)
    std::cout << "ROS integration:\n";
    std::cout << "  tf2::toMsg(Eigen::Isometry3d) -> geometry_msgs::Pose\n";
    std::cout << "  tf2::fromMsg(geometry_msgs::Pose) -> Eigen::Isometry3d\n\n";

    std::cout << "Key points:\n";
    std::cout << "- OpenCV uses row-major, Eigen uses column-major by default\n";
    std::cout << "- Use Eigen::Map to avoid copying data\n";
    std::cout << "- Be careful with data ownership\n";

    return 0;
}
