/**
 * Chapter 1.5: Block Operations
 *
 * Topics: Block extraction, corner operations, row/column access
 * Crucial for SLAM: extracting rotation/translation from transformation matrices
 */

#include <iostream>
#include <Eigen/Dense>


int main() {
    std::cout << "=== 1.5 Block Operations ===\n\n";

    Eigen::Matrix4d transform = Eigen::Matrix4d::Identity();
    transform.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    transform.block<3,1>(0,3) = Eigen::Vector3d(1, 2, 3);

    std::cout << "Transformation matrix:\n" << transform << "\n\n";

    // Extract rotation
    // (0,0) 에서부터 3x3 블록 추출
    Eigen::Matrix3d rotation = transform.block<3,3>(0,0);
    std::cout << "Extracted rotation:\n" << rotation << "\n\n";

    // Extract translation
    Eigen::Vector3d translation = transform.block<3,1>(0,3);
    std::cout << "Extracted translation: \n" << translation << "\n\n";

    // Corner operations
    std::cout << "Top-left 2x2:\n" << transform.topLeftCorner<2,2>() << "\n\n";
    std::cout << "Bottom-right 2x2:\n" << transform.bottomRightCorner<2,2>() << "\n\n";

    // Row and column access
    std::cout << "First row: " << transform.row(0) << "\n";
    std::cout << "First column:\n" << transform.col(0) << "\n\n";

    return 0;
}
