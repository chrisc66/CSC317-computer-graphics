#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  U.resize(V.rows(),V.cols());
  for (int i = 0; i < V.rows(); i++){
    Eigen::Vector4d u_row = Eigen::Vector4d::Zero();  // temporary variable to store each row of u
    for (int j = 0; j < skeleton.size(); j++){
      if (skeleton[j].weight_index >= 0)
        u_row += W(i,skeleton[j].weight_index) * (T[j] * Eigen::Vector4d(V(i,0),V(i,1),V(i,2),1));
    }
    U(i,0) = u_row(0);
    U(i,1) = u_row(1);
    U(i,2) = u_row(2);
  }
  /////////////////////////////////////////////////////////////////////////////
}
