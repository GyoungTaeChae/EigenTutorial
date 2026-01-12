/**
 * Chapter 5.5: Direct Sparse Solvers
 *
 * Topics: SimplicialLLT, SimplicialLDLT, SparseLU
 */

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseCholesky>

int main() {
    std::cout << "=== 5.5 Direct Sparse Solvers ===\n\n";

    // Create SPD sparse matrix
    typedef Eigen::Triplet<double> T;
    std::vector<T> triplets;

    triplets.push_back(T(0, 0, 4.0));
    triplets.push_back(T(0, 1, -1.0));
    triplets.push_back(T(1, 0, -1.0));
    triplets.push_back(T(1, 1, 4.0));
    triplets.push_back(T(1, 2, -1.0));
    triplets.push_back(T(2, 1, -1.0));
    triplets.push_back(T(2, 2, 4.0));
    triplets.push_back(T(2, 3, -1.0));
    triplets.push_back(T(3, 2, -1.0));
    triplets.push_back(T(3, 3, 4.0));
    triplets.push_back(T(3, 4, -1.0));
    triplets.push_back(T(4, 3, -1.0));
    triplets.push_back(T(4, 4, 4.0));

    Eigen::SparseMatrix<double> A_sparse(5, 5);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    Eigen::VectorXd b_sparse(5);
    b_sparse << 1, 2, 3, 4, 5;

    // SimplicialLLT: Cholesky for SPD matrices (fast)
    Eigen::SimplicialLLT<Eigen::SparseMatrix<double>> solver_llt;
    solver_llt.compute(A_sparse);
    if (solver_llt.info() != Eigen::Success) {
        std::cout << "LLT decomposition failed!\n";
    } else {
        Eigen::VectorXd x_llt = solver_llt.solve(b_sparse);
        std::cout << "SimplicialLLT solution: " << x_llt.transpose() << "\n";
        std::cout << "Residual: " << (A_sparse * x_llt - b_sparse).norm() << "\n\n";
    }

    // SimplicialLDLT: LDLT for symmetric matrices
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> solver_ldlt;
    solver_ldlt.compute(A_sparse);
    if (solver_ldlt.info() != Eigen::Success) {
        std::cout << "LDLT decomposition failed!\n";
    } else {
        Eigen::VectorXd x_ldlt = solver_ldlt.solve(b_sparse);
        std::cout << "SimplicialLDLT solution: " << x_ldlt.transpose() << "\n\n";
    }

    // SparseLU: General sparse matrices
    Eigen::SparseMatrix<double> A_general(3, 3);
    std::vector<T> trip_gen;
    trip_gen.push_back(T(0, 0, 2.0));
    trip_gen.push_back(T(0, 1, 1.0));
    trip_gen.push_back(T(1, 0, 1.0));
    trip_gen.push_back(T(1, 1, 3.0));
    trip_gen.push_back(T(1, 2, 1.0));
    trip_gen.push_back(T(2, 1, 1.0));
    trip_gen.push_back(T(2, 2, 2.0));
    A_general.setFromTriplets(trip_gen.begin(), trip_gen.end());

    Eigen::VectorXd b_gen(3);
    b_gen << 1, 2, 3;

    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver_lu;
    solver_lu.compute(A_general);
    if (solver_lu.info() != Eigen::Success) {
        std::cout << "LU decomposition failed!\n";
    } else {
        Eigen::VectorXd x_lu = solver_lu.solve(b_gen);
        std::cout << "SparseLU solution: " << x_lu.transpose() << "\n";
        std::cout << "Residual: " << (A_general * x_lu - b_gen).norm() << "\n";
    }

    return 0;
}
