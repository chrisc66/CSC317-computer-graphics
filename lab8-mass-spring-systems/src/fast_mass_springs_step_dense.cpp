#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // large penalty for the penalty method 
  const double w = 1e10;
  const int v_rows = V.rows();
  const int e_rows = E.rows();

  // Calculate matrix Unext
  Unext.resize(Ucur.rows(), Ucur.cols());

  Eigen::MatrixXd d = Eigen::MatrixXd::Zero(e_rows, 3);
  Eigen::MatrixXd l = Eigen::MatrixXd::Zero(v_rows, 3);

  for (int i = 0; i < 50; i ++){
      for (int j = 0; j < e_rows; j ++){
          // d[j] = (Unext[j0] - Unext[j1]).norm * r[j]
          d.row(j) = (Unext.row(E(j, 0)) - Unext.row(E(j, 1))).normalized() * r[j];
      }
      // l = k*At*d + M*(2Ucur-Uprev)/dt^2 + fext + w*Ct*C*V
      l = k * A.transpose() * d + M * (2 * Ucur - Uprev) / pow(delta_t, 2) + fext + w * C.transpose() * C * V;
      Unext = prefactorization.solve(l);
  }

  //////////////////////////////////////////////////////////////////////////////
}
