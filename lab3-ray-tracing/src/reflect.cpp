#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Equation reference textbook 4.8 p87
  // r = d - 2(d.n)n --- equation (4.5)
  Eigen::Vector3d out = in - 2 * (in.dot(n)) * n;
  return out.normalized();
  ////////////////////////////////////////////////////////////////////////////
}
