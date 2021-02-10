#include "first_hit.h"
#include <iostream>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  hit_id = -1;
  bool intersect = false;
  double smallest_t = INFINITY;
  Eigen::Vector3d smallest_n;
  
  for (int i = 0; i < objects.size(); i ++){
    if (objects[i]->intersect(ray, min_t, t, n)){
      intersect = true;
      if (t < smallest_t){
        // if intersect and smaller distance t
        // update hit_id with smallest t value
        hit_id = i;
        smallest_t = t;
        smallest_n = n;
      }
    }
  }
  if (!intersect)
    return false;
  t = smallest_t;
  n = smallest_n;
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
