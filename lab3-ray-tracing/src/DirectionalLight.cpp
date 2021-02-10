#include "DirectionalLight.h"
#include <limits>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  max_t = std::numeric_limits<double>::infinity();
  d = (-this->d).normalized();
  return;
  ////////////////////////////////////////////////////////////////////////////
}
