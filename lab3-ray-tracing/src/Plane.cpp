#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Equation reference lecture slides lecture2 ray casting p62

  // Ray: origin e, direction d
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  // Plane: point p, normal n
  Eigen::Vector3d p = point;
  Eigen::Vector3d norm = normal;

  if (n.dot(d) != 0){
    // Find t value
    t = (norm.dot(p - e)) / (norm.dot(d));
    // Find unit vector n 
    n = norm/norm.norm();
    if (t > min_t)
      return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

