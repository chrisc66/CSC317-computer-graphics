#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <iostream>
#include <vector>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Equation reference Möller–Trumbore Intersection Algorithm
  // https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm

  // Tolerance error value
  const double EPSILON = 0.001;
  // Ray: origin e, direction d
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  // Triangle corners: a, b, c
  Eigen::Vector3d a = std::get<0>(corners);
  Eigen::Vector3d b = std::get<1>(corners);
  Eigen::Vector3d c = std::get<2>(corners);
  // Triangle lines between corners: ab, ac, bc
  Eigen::Vector3d ab = a - b;
  Eigen::Vector3d bc = b - c;
  Eigen::Vector3d ac = a - c;

  // Find unit vector n 
  n = ab.cross(bc) / (ab.cross(bc)).norm();

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
  else
    return false;
  ////////////////////////////////////////////////////////////////////////////
}


