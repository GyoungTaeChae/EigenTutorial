/**
 * Chapter 7.2: Eigen::Map - Zero-Copy Data Access
 *
 * Topics: Mapping external memory, interfacing with other libraries
 */

#include <iostream>
#include <Eigen/Dense>

int main() {
    std::cout << "=== 7.2 Eigen::Map ===\n\n";

    // Map allows Eigen to work with existing memory without copying
    // Essential for interfacing with:
    // - Raw arrays
    // - OpenCV matrices
    // - ROS messages
    // - C libraries

    // Map from raw array
    double raw_data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Map as 3x3 matrix (column-major by default)
    Eigen::Map<Eigen::Matrix3d> mapped_mat(raw_data);
    std::cout << "Mapped matrix (column-major):\n" << mapped_mat << "\n\n";

    // Modifying map modifies original data!
    mapped_mat(0, 0) = 100;
    std::cout << "After modification, raw_data[0] = " << raw_data[0] << "\n\n";

    // Map as vector
    double vec_data[5] = {1, 2, 3, 4, 5};
    Eigen::Map<Eigen::VectorXd> mapped_vec(vec_data, 5);
    std::cout << "Mapped vector: " << mapped_vec.transpose() << "\n\n";

    // Row-major mapping (for OpenCV compatibility)
    double row_major_data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor>> row_mapped(row_major_data);
    std::cout << "Row-major mapped matrix:\n" << row_mapped << "\n\n";

    // Map with stride (for interleaved data)
    double interleaved[12] = {1, 0, 0, 2, 0, 0, 3, 0, 0, 4, 0, 0};  // R, G, B...
    Eigen::Map<Eigen::VectorXd, 0, Eigen::InnerStride<3>> r_channel(interleaved, 4);
    std::cout << "R channel from interleaved: " << r_channel.transpose() << "\n";

    return 0;
}
