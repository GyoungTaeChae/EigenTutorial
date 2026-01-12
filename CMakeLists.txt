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
function(add_chapter_executable chapter_num name)
    set(target_name "${chapter_num}_${name}")
    add_executable(${target_name} src/chapter${chapter_num}/${name}.cpp)
    target_link_libraries(${target_name} Eigen3::Eigen)
endfunction()

# ===== Chapter 1: Basic Linear Algebra =====
add_chapter_executable(1 declaration)
add_chapter_executable(1 initialization)
add_chapter_executable(1 basic_operations)
add_chapter_executable(1 vector_operations)
add_chapter_executable(1 block_operations)
add_chapter_executable(1 element_wise_operations)
add_chapter_executable(1 point_transformation)

# ===== Chapter 2: Matrix Decompositions =====
add_chapter_executable(2 svd)
add_chapter_executable(2 svd_point_cloud_alignment)
add_chapter_executable(2 qr_decomposition)
add_chapter_executable(2 cholesky_decomposition)
add_chapter_executable(2 lu_decomposition)
add_chapter_executable(2 eigenvalue_decomposition)
add_chapter_executable(2 essential_matrix)

# ===== Chapter 3: Geometry Module =====
add_chapter_executable(3 rotation_matrix)
add_chapter_executable(3 quaternion)
add_chapter_executable(3 angle_axis)
add_chapter_executable(3 euler_angles)
add_chapter_executable(3 isometry3d)
add_chapter_executable(3 affine3d)
add_chapter_executable(3 conversions)
add_chapter_executable(3 camera_pose)
add_chapter_executable(3 pose_composition)
add_chapter_executable(3 small_angle_approximation)

# ===== Chapter 4: Solving Linear Systems =====
add_chapter_executable(4 square_systems)
add_chapter_executable(4 spd_systems)
add_chapter_executable(4 overdetermined_systems)
add_chapter_executable(4 underdetermined_systems)
add_chapter_executable(4 weighted_least_squares)
add_chapter_executable(4 multiple_rhs)
add_chapter_executable(4 solution_quality)
add_chapter_executable(4 triangulation)
add_chapter_executable(4 pnp)

# ===== Chapter 5: Sparse Matrices =====
add_chapter_executable(5 why_sparse)
add_chapter_executable(5 creating_sparse)
add_chapter_executable(5 sparse_operations)
add_chapter_executable(5 iterating_sparse)
add_chapter_executable(5 direct_solvers)
add_chapter_executable(5 iterative_solvers)
add_chapter_executable(5 pose_graph_hessian)
add_chapter_executable(5 block_sparse)
add_chapter_executable(5 performance_tips)

# ===== Chapter 6: Optimization Basics =====
add_chapter_executable(6 jacobians)
add_chapter_executable(6 numerical_jacobian)
add_chapter_executable(6 least_squares)
add_chapter_executable(6 gauss_newton)
add_chapter_executable(6 levenberg_marquardt)
add_chapter_executable(6 se3_jacobians)
add_chapter_executable(6 reprojection_error)
add_chapter_executable(6 robust_cost_functions)
add_chapter_executable(6 simple_ba)

# ===== Chapter 7: Practical Skills =====
add_chapter_executable(7 memory_alignment)
add_chapter_executable(7 eigen_map)
add_chapter_executable(7 avoiding_temporaries)
add_chapter_executable(7 expression_templates)
add_chapter_executable(7 common_pitfalls)
add_chapter_executable(7 performance_tips)
add_chapter_executable(7 integration)
add_chapter_executable(7 debugging_tips)
add_chapter_executable(7 slam_patterns)

# Custom target to run all chapters in sequence
add_custom_target(run_chapter1
    COMMAND echo "=== Chapter 1: Basic Linear Algebra ==="
    COMMAND ./1_declaration
    COMMAND ./1_initialization
    COMMAND ./1_basic_operations
    COMMAND ./1_vector_operations
    COMMAND ./1_block_operations
    COMMAND ./1_element_wise_operations
    COMMAND ./1_point_transformation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 1..."
)

add_custom_target(run_chapter2
    COMMAND echo "=== Chapter 2: Matrix Decompositions ==="
    COMMAND ./2_svd
    COMMAND ./2_svd_point_cloud_alignment
    COMMAND ./2_qr_decomposition
    COMMAND ./2_cholesky_decomposition
    COMMAND ./2_lu_decomposition
    COMMAND ./2_eigenvalue_decomposition
    COMMAND ./2_essential_matrix
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 2..."
)

add_custom_target(run_chapter3
    COMMAND echo "=== Chapter 3: Geometry Module ==="
    COMMAND ./3_rotation_matrix
    COMMAND ./3_quaternion
    COMMAND ./3_angle_axis
    COMMAND ./3_euler_angles
    COMMAND ./3_isometry3d
    COMMAND ./3_affine3d
    COMMAND ./3_conversions
    COMMAND ./3_camera_pose
    COMMAND ./3_pose_composition
    COMMAND ./3_small_angle_approximation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 3..."
)

add_custom_target(run_chapter4
    COMMAND echo "=== Chapter 4: Solving Linear Systems ==="
    COMMAND ./4_square_systems
    COMMAND ./4_spd_systems
    COMMAND ./4_overdetermined_systems
    COMMAND ./4_underdetermined_systems
    COMMAND ./4_weighted_least_squares
    COMMAND ./4_multiple_rhs
    COMMAND ./4_solution_quality
    COMMAND ./4_triangulation
    COMMAND ./4_pnp
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 4..."
)

add_custom_target(run_chapter5
    COMMAND echo "=== Chapter 5: Sparse Matrices ==="
    COMMAND ./5_why_sparse
    COMMAND ./5_creating_sparse
    COMMAND ./5_sparse_operations
    COMMAND ./5_iterating_sparse
    COMMAND ./5_direct_solvers
    COMMAND ./5_iterative_solvers
    COMMAND ./5_pose_graph_hessian
    COMMAND ./5_block_sparse
    COMMAND ./5_performance_tips
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 5..."
)

add_custom_target(run_chapter6
    COMMAND echo "=== Chapter 6: Optimization Basics ==="
    COMMAND ./6_jacobians
    COMMAND ./6_numerical_jacobian
    COMMAND ./6_least_squares
    COMMAND ./6_gauss_newton
    COMMAND ./6_levenberg_marquardt
    COMMAND ./6_se3_jacobians
    COMMAND ./6_reprojection_error
    COMMAND ./6_robust_cost_functions
    COMMAND ./6_simple_ba
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 6..."
)

add_custom_target(run_chapter7
    COMMAND echo "=== Chapter 7: Practical Skills ==="
    COMMAND ./7_memory_alignment
    COMMAND ./7_eigen_map
    COMMAND ./7_avoiding_temporaries
    COMMAND ./7_expression_templates
    COMMAND ./7_common_pitfalls
    COMMAND ./7_performance_tips
    COMMAND ./7_integration
    COMMAND ./7_debugging_tips
    COMMAND ./7_slam_patterns
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Chapter 7..."
)
