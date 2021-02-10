#include "ray_intersect_triangle.h"

#include <Eigen/Geometry>
#include <vector>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Re-using code from previous assignment 

  // Tolerance error value
  const double EPSILON = 0.001;
  // Ray: origin e, direction d
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  // Triangle corners: a, b, c
  Eigen::Vector3d a = (Eigen::Vector3d) A;
  Eigen::Vector3d b = (Eigen::Vector3d) B;
  Eigen::Vector3d c = (Eigen::Vector3d) C;
  // Triangle lines between corners: ab, ac, bc
  Eigen::Vector3d ab = a - b;
  Eigen::Vector3d bc = b - c;
  Eigen::Vector3d ac = a - c;

  // Find unit vector n 
  Eigen::Vector3d n = ab.cross(bc) / (ab.cross(bc)).norm();

  // Find the smallest t value (larger than min_t)
  double ta = (n.dot(a) - n.dot(e)) / (n.dot(d));
  double tb = (n.dot(b) - n.dot(e)) / (n.dot(d));
  double tc = (n.dot(c) - n.dot(e)) / (n.dot(d));
  std::vector<double> t_vec {ta, tb, tc};
  std::sort(t_vec.begin(), t_vec.end()); // smallest -> largest
  if (t_vec[0] >= min_t)
    t = t_vec[0];
  else if (t_vec[1] >= min_t)
    t = t_vec[1];
  else if (t_vec[2] >= min_t)
    t = t_vec[2];
  else
    return false;

  // verify that intersect p is within the toleranced range
  Eigen::Vector3d p = e + t * d;
  // Triangle lines from corner to intersect: ab, ac, bc
  Eigen::Vector3d ap = a - p;
  Eigen::Vector3d bp = b - p;
  Eigen::Vector3d cp = c - p;

  double offset = abs(ap.cross(bp).norm() + ap.cross(cp).norm() + bp.cross(cp).norm()) / ab.cross(bc).norm();
  if (1 - EPSILON < offset && offset < 1 + EPSILON)
    return true;
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

