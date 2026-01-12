cmake_minimum_required(VERSION 3.10)
project(EigenTutorial)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Eigen3
find_package(Eigen3 REQUIRED)

# Include Eigen headers
include_directories(${EIGEN3_INCLUDE_DIR})

# Optimization flags for release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra")

# Helper function to create executables
# Usage: add_chapter_executable(chapter_num section_num name)
# Example: add_chapter_executable(1 1 declaration) creates target "1.1.declaration" from "src/chapter1/1.1.declaration.cpp"
function(add_chapter_executable chapter_num section_num name)
    set(target_name "${chapter_num}.${section_num}.${name}")
    add_executable(${target_name} src/chapter${chapter_num}/${chapter_num}.${section_num}.${name}.cpp)
    target_link_libraries(${target_name} Eigen3::Eigen)
endfunction()

# ===== Chapter 1: Basic Linear Algebra =====
add_chapter_executable(1 1 declaration)
add_chapter_executable(1 2 initialization)
add_chapter_executable(1 3 basic_operations)
add_chapter_executable(1 4 vector_operations)
add_chapter_executable(1 5 block_operations)
add_chapter_executable(1 6 element_wise_operations)
add_chapter_executable(1 7 point_transformation)

# ===== Chapter 2: Matrix Decompositions =====
add_chapter_executable(2 1 svd)
add_chapter_executable(2 2 svd_point_cloud_alignment)
add_chapter_executable(2 3 qr_decomposition)
add_chapter_executable(2 4 cholesky_decomposition)
add_chapter_executable(2 5 lu_decomposition)
add_chapter_executable(2 6 eigenvalue_decomposition)
add_chapter_executable(2 7 essential_matrix)

# ===== Chapter 3: Geometry Module =====
add_chapter_executable(3 1 rotation_matrix)
add_chapter_executable(3 2 quaternion)
add_chapter_executable(3 3 angle_axis)
add_chapter_executable(3 4 euler_angles)
add_chapter_executable(3 5 isometry3d)
add_chapter_executable(3 6 affine3d)
add_chapter_executable(3 7 conversions)
add_chapter_executable(3 8 camera_pose)
add_chapter_executable(3 9 pose_composition)
add_chapter_executable(3 10 small_angle_approximation)

# ===== Chapter 4: Solving Linear Systems =====
add_chapter_executable(4 1 square_systems)
add_chapter_executable(4 2 spd_systems)
add_chapter_executable(4 3 overdetermined_systems)
add_chapter_executable(4 4 underdetermined_systems)
add_chapter_executable(4 5 weighted_least_squares)
add_chapter_executable(4 6 multiple_rhs)
add_chapter_executable(4 7 solution_quality)
add_chapter_executable(4 8 triangulation)
add_chapter_executable(4 9 pnp)

# ===== Chapter 5: Sparse Matrices =====
add_chapter_executable(5 1 why_sparse)
add_chapter_executable(5 2 creating_sparse)
add_chapter_executable(5 3 sparse_operations)
add_chapter_executable(5 4 iterating_sparse)
add_chapter_executable(5 5 direct_solvers)
add_chapter_executable(5 6 iterative_solvers)
add_chapter_executable(5 7 pose_graph_hessian)
add_chapter_executable(5 8 block_sparse)
add_chapter_executable(5 9 performance_tips)

# ===== Chapter 6: Optimization Basics =====
add_chapter_executable(6 1 jacobians)
add_chapter_executable(6 2 numerical_jacobian)
add_chapter_executable(6 3 least_squares)
add_chapter_executable(6 4 gauss_newton)
add_chapter_executable(6 5 levenberg_marquardt)
add_chapter_executable(6 6 se3_jacobians)
add_chapter_executable(6 7 reprojection_error)
add_chapter_executable(6 8 robust_cost_functions)
add_chapter_executable(6 9 simple_ba)

# ===== Chapter 7: Practical Skills =====
add_chapter_executable(7 1 memory_alignment)
add_chapter_executable(7 2 eigen_map)
add_chapter_executable(7 3 avoiding_temporaries)
add_chapter_executable(7 4 expression_templates)
add_chapter_executable(7 5 common_pitfalls)
add_chapter_executable(7 6 performance_tips)
add_chapter_executable(7 7 integration)
add_chapter_executable(7 8 debugging_tips)
add_chapter_executable(7 9 slam_patterns)

# Custom target to run all chapters in sequence
add_custom_target(run_chapter1
    COMMAND echo "=== Chapter 1: Basic Linear Algebra ==="
    COMMAND ./1.1.declaration
    COMMAND ./1.2.initialization
    COMMAND ./1.3.basic_operations
    COMMAND ./1.4.vector_operations
    COMMAND ./1.5.block_operations
    COMMAND ./1.6.element_wise_operations
    COMMAND ./1.7.point_transformation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 1..."
)

add_custom_target(run_chapter2
    COMMAND echo "=== Chapter 2: Matrix Decompositions ==="
    COMMAND ./2.1.svd
    COMMAND ./2.2.svd_point_cloud_alignment
    COMMAND ./2.3.qr_decomposition
    COMMAND ./2.4.cholesky_decomposition
    COMMAND ./2.5.lu_decomposition
    COMMAND ./2.6.eigenvalue_decomposition
    COMMAND ./2.7.essential_matrix
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 2..."
)

add_custom_target(run_chapter3
    COMMAND echo "=== Chapter 3: Geometry Module ==="
    COMMAND ./3.1.rotation_matrix
    COMMAND ./3.2.quaternion
    COMMAND ./3.3.angle_axis
    COMMAND ./3.4.euler_angles
    COMMAND ./3.5.isometry3d
    COMMAND ./3.6.affine3d
    COMMAND ./3.7.conversions
    COMMAND ./3.8.camera_pose
    COMMAND ./3.9.pose_composition
    COMMAND ./3.10.small_angle_approximation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 3..."
)

add_custom_target(run_chapter4
    COMMAND echo "=== Chapter 4: Solving Linear Systems ==="
    COMMAND ./4.1.square_systems
    COMMAND ./4.2.spd_systems
    COMMAND ./4.3.overdetermined_systems
    COMMAND ./4.4.underdetermined_systems
    COMMAND ./4.5.weighted_least_squares
    COMMAND ./4.6.multiple_rhs
    COMMAND ./4.7.solution_quality
    COMMAND ./4.8.triangulation
    COMMAND ./4.9.pnp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 4..."
)

add_custom_target(run_chapter5
    COMMAND echo "=== Chapter 5: Sparse Matrices ==="
    COMMAND ./5.1.why_sparse
    COMMAND ./5.2.creating_sparse
    COMMAND ./5.3.sparse_operations
    COMMAND ./5.4.iterating_sparse
    COMMAND ./5.5.direct_solvers
    COMMAND ./5.6.iterative_solvers
    COMMAND ./5.7.pose_graph_hessian
    COMMAND ./5.8.block_sparse
    COMMAND ./5.9.performance_tips
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 5..."
)

add_custom_target(run_chapter6
    COMMAND echo "=== Chapter 6: Optimization Basics ==="
    COMMAND ./6.1.jacobians
    COMMAND ./6.2.numerical_jacobian
    COMMAND ./6.3.least_squares
    COMMAND ./6.4.gauss_newton
    COMMAND ./6.5.levenberg_marquardt
    COMMAND ./6.6.se3_jacobians
    COMMAND ./6.7.reprojection_error
    COMMAND ./6.8.robust_cost_functions
    COMMAND ./6.9.simple_ba
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 6..."
)

add_custom_target(run_chapter7
    COMMAND echo "=== Chapter 7: Practical Skills ==="
    COMMAND ./7.1.memory_alignment
    COMMAND ./7.2.eigen_map
    COMMAND ./7.3.avoiding_temporaries
    COMMAND ./7.4.expression_templates
    COMMAND ./7.5.common_pitfalls
    COMMAND ./7.6.performance_tips
    COMMAND ./7.7.integration
    COMMAND ./7.8.debugging_tips
    COMMAND ./7.9.slam_patterns
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 7..."
)
