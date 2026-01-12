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

using namespace std;
using namespace Eigen;

int main() {
    cout << "=== 5.5 Direct Sparse Solvers ===\n\n";

    // Create SPD sparse matrix
    typedef Triplet<double> T;
    vector<T> triplets;

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

    SparseMatrix<double> A_sparse(5, 5);
    A_sparse.setFromTriplets(triplets.begin(), triplets.end());

    VectorXd b_sparse(5);
    b_sparse << 1, 2, 3, 4, 5;

    // SimplicialLLT: Cholesky for SPD matrices (fast)
    SimplicialLLT<SparseMatrix<double>> solver_llt;
    solver_llt.compute(A_sparse);
    if (solver_llt.info() != Success) {
        cout << "LLT decomposition failed!\n";
    } else {
        VectorXd x_llt = solver_llt.solve(b_sparse);
        cout << "SimplicialLLT solution: " << x_llt.transpose() << "\n";
        cout << "Residual: " << (A_sparse * x_llt - b_sparse).norm() << "\n\n";
    }

    // SimplicialLDLT: LDLT for symmetric matrices
    SimplicialLDLT<SparseMatrix<double>> solver_ldlt;
    solver_ldlt.compute(A_sparse);
    if (solver_ldlt.info() != Success) {
        cout << "LDLT decomposition failed!\n";
    } else {
        VectorXd x_ldlt = solver_ldlt.solve(b_sparse);
        cout << "SimplicialLDLT solution: " << x_ldlt.transpose() << "\n\n";
    }

    // SparseLU: General sparse matrices
    SparseMatrix<double> A_general(3, 3);
    vector<T> trip_gen;
    trip_gen.push_back(T(0, 0, 2.0));
    trip_gen.push_back(T(0, 1, 1.0));
    trip_gen.push_back(T(1, 0, 1.0));
    trip_gen.push_back(T(1, 1, 3.0));
    trip_gen.push_back(T(1, 2, 1.0));
    trip_gen.push_back(T(2, 1, 1.0));
    trip_gen.push_back(T(2, 2, 2.0));
    A_general.setFromTriplets(trip_gen.begin(), trip_gen.end());

    VectorXd b_gen(3);
    b_gen << 1, 2, 3;

    SparseLU<SparseMatrix<double>> solver_lu;
    solver_lu.compute(A_general);
    if (solver_lu.info() != Success) {
        cout << "LU decomposition failed!\n";
    } else {
        VectorXd x_lu = solver_lu.solve(b_gen);
        cout << "SparseLU solution: " << x_lu.transpose() << "\n";
        cout << "Residual: " << (A_general * x_lu - b_gen).norm() << "\n";
    }

    return 0;
}
