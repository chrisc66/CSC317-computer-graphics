#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  
  // function handle that computes the least-squares objective value given a
  // #bones list of Euler angles
  // Reference: https://eigen.tuxfamily.org/dox/classEigen_1_1MatrixBase.html#ac8da566526419f9742a6c471bbd87e0a
  // Using Eigen squaredNorm() to calculate total energy
  f = [&](const Eigen::VectorXd & A) -> double {
      Skeleton copy = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd tips = transformed_tips(copy, b);
      // total energy = sum of (tips - xb0) ^2
      return (tips - xb0).squaredNorm();
  };


  // function handle that computes the least-squares objective gradient
  // given a #bones list of Euler angles 
  grad_f = [&](const Eigen::VectorXd & A) -> Eigen::VectorXd {
    Skeleton copy = copy_skeleton_at(skeleton, A);
    Eigen::VectorXd tips = transformed_tips(copy, b);
    Eigen::MatrixXd J;
    kinematics_jacobian(copy, b, J);
    // gradient = 2 * J trans * (tips - xb0)
    return 2 * J.transpose() * (tips - xb0);
  };


  // function handle that projects a given set of Euler angles onto the
  // input skeleton's joint angles
  proj_z = [&](Eigen::VectorXd & A) {
    assert(skeleton.size()*3 == A.size());
    for (int i = 0; i < skeleton.size(); i ++){
      A[i*3+0] = std::max(skeleton[i].xzx_min[0], std::min(skeleton[i].xzx_max[0], A[3*i+0]));
      A[i*3+1] = std::max(skeleton[i].xzx_min[1], std::min(skeleton[i].xzx_max[1], A[3*i+1]));
      A[i*3+2] = std::max(skeleton[i].xzx_min[2], std::min(skeleton[i].xzx_max[2], A[3*i+2]));
    }
  };
  /////////////////////////////////////////////////////////////////////////////
}
