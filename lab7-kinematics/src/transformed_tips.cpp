#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> >  T;
  forward_kinematics(skeleton,T);

  Eigen::VectorXd tips = Eigen::VectorXd::Zero(3*b.size());   // tip position matrix
  Eigen::Vector4d tip_row = Eigen::Vector4d::Zero();          // temporary variable to store each row of tips
  
  for (int i = 0; i < b.size(); i ++){
    tip_row = T[b(i)] * skeleton[b[i]].rest_T * Eigen::Vector4d(skeleton[b(i)].length, 0, 0, 1);
    tips(3*i+0) = tip_row(0);
    tips(3*i+1) = tip_row(1);
    tips(3*i+2) = tip_row(2);
  }

  return tips;
  /////////////////////////////////////////////////////////////////////////////
}
