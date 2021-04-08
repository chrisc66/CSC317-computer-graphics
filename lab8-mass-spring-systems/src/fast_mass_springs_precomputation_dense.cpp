#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // introducing large penalty for the penalty method 
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

  // calculate matrix M
  M = Eigen::MatrixXd::Zero(v_rows, v_rows);
  for (int i = 0; i < v_rows; i ++) {
      M(i, i) = m[i];
  }

  // calculate matrix A
  signed_incidence_matrix_dense(v_rows, E, A);

  // calculate matrix C
  C = Eigen::MatrixXd::Zero(b_rows, v_rows);
  for (int i = 0; i < b_rows; i ++) {
      C(i, b(i)) = 1;
  }

  // calculate decomposition matrix prefactorization
  Eigen::MatrixXd Q = (k * A.transpose() * A) + (M / pow(delta_t, 2)) + w * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
