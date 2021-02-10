#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <algorithm>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Equation reference textbook 4.5.2 p83
  // h = v + l (unit vector)
  // rgb = kd * I * max(0, n*l) + ks * I * max(0, n*h)^p

  double inf = std::numeric_limits<double>::infinity();
  // Epsilon as min_t, the second parameter in first_hit
  const double MIN_T = 0.1;
  // return value rgb
  Eigen::Vector3d rgb(0,0,0);
  // Preparing rgb calculation: kd, ks, p values
  Eigen::Vector3d kd = objects[hit_id]->material->kd;
  Eigen::Vector3d ks = objects[hit_id]->material->ks;
  double p = objects[hit_id]->material->phong_exponent;

  // Declaring variables outside for loop
  // Variables for direction
  Eigen::Vector3d v;
  Eigen::Vector3d l;
  double max_t;
  // Variables for first_hit
  Ray check_ray;
  int check_hit_id;
  double check_t;
  Eigen::Vector3d check_n;
  bool hit = false;
  // Variables for rgb calculation: I & h
  Eigen::Vector3d I;
  Eigen::Vector3d h;

  for (int i = 0; i < lights.size(); i ++){
    // Preparing rgb calculation: l value, and condition check max_t
    v = ray.origin + t * ray.direction;
    lights[i]->direction(v,l,max_t);

    // Variables for first_hit, and condition check check_t
    check_ray.origin = v;
    check_ray.direction = l;
    hit = first_hit(check_ray,MIN_T,objects,check_hit_id,check_t,check_n);

    // Proceed if not hit or check_t valid, find h and rgb value
    if ( !hit || check_t > max_t ) {
      // Preparing rgb calculation: I & h value
      I = lights[i]->I;
      v = (-ray.direction).normalized();
      h = (v + l).normalized();
      rgb += (kd.array() * (I.array())).matrix() * fmax(0, l.dot(n)) + (ks.array() * (I.array())).matrix() * std::pow(fmax(0, h.dot(n)), p);
    }
  }
  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
