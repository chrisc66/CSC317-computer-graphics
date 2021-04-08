#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // large penalty for the penalty method 
  const double w = 1e10;
  const int e_rows = E.rows();
  const int v_rows = V.rows();
  const int b_rows = b.rows();
  
  // calculate matrix r
  r = Eigen::VectorXd::Zero(e_rows);
  for (int i = 0; i < e_rows; i ++) {
      // r[i] = (vi0 - vi1).norm
      r[i] = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }

  // calculate sparse matrix M
  std::vector<Eigen::Triplet<double> > ijv_1;
  ijv_1.reserve(v_rows);
  
  for (int i = 0; i < v_rows; i ++) {
      ijv_1.emplace_back(i, i, m[i]);
  }

  M.resize(v_rows, v_rows);
  M.setFromTriplets(ijv_1.begin(), ijv_1.end());

  // calculate sparse matrix A
  signed_incidence_matrix_sparse(v_rows, E, A);

  // calculate sparse matrix C
  std::vector<Eigen::Triplet<double> > ijv_2;
  ijv_2.reserve(b_rows);
  
  for (int i = 0; i < b_rows; i ++) {
      ijv_2.emplace_back(i, b(i), 1);
  }

  C.resize(b_rows, v_rows);
  C.setFromTriplets(ijv_2.begin(), ijv_2.end());

  // calculate decomposition matrix prefactorization
  Eigen::SparseMatrix<double> Q = (k * A.transpose() * A) + (M / pow(delta_t, 2)) + w * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
