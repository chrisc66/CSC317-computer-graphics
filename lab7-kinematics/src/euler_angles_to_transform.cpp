#include "euler_angles_to_transform.h"

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  return (Eigen::Affine3d) Eigen::AngleAxisd(M_PI * xzx(2) / 180, Eigen::Vector3d::UnitX()) *
                          Eigen::AngleAxisd(M_PI * xzx(1) / 180, Eigen::Vector3d::UnitZ()) *
                          Eigen::AngleAxisd(M_PI * xzx(0) / 180, Eigen::Vector3d::UnitX());
  /////////////////////////////////////////////////////////////////////////////
}
