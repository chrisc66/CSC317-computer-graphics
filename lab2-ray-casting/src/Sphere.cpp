#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Equation reference textbook 4.4.1 p77
  
  // Ray: origin e, direction d
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  // Sphere: center c, radius r
  Eigen::Vector3d c = center;
  double r = radius;
  
  // B^2 - 4AC 
  double discriminant = pow(d.dot(e-c),2) - d.dot(d) * ((e-c).dot(e-c) - pow(r, 2));
  bool intersect = false;

  if (discriminant >= 0) {
    // Find the smallest t value (larger than min_t) 
    double t1 = (-d.dot(e-c) + sqrt(discriminant)) / d.dot(d);
    double t2 = (-d.dot(e-c) - sqrt(discriminant)) / d.dot(d);
    // There are six cases in total
    //   t1    > t2    > min_t --> t2
    //   t2    > t1    > min_t --> t1
    //   t1    > min_t > t2    --> t1
    //   t2    > min_t > t1    --> t2
    //   min_t > t1    > t2    --> none
    //   min_t > t2    > t1    --> none
    if (t1 >= t2 && t2 >= min_t) {
      intersect = true;
      t = t2;
    }
    else if (t2 >= t1 && t1 >= min_t) {
      intersect = true;
      t = t1;
    } 
    else if (t1 >= min_t && min_t > t2){
      intersect = true;
      t = t1;
    }
    else if (t2 >= min_t) {
      intersect = true;
      t = t2;
    }
    else {
      intersect = false;
    }

    // Find unit vector n 
    n = e + t * d - c;
    n = n / n.norm();
  }
  
  return intersect;

  ////////////////////////////////////////////////////////////////////////////
}
