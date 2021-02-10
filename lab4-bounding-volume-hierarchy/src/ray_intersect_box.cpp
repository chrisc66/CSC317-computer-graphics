#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  // Find max and min x,y,z values between ray and corner
  // Txmin = (Xmin - Xe) / Xd
  // Txmax = (Xmax - Xe) / Xd
  double t_x_min = (box.min_corner(0) - ray.origin(0)) / ray.direction(0);
  double t_x_max = (box.max_corner(0) - ray.origin(0)) / ray.direction(0);
  double t_y_min = (box.min_corner(1) - ray.origin(1)) / ray.direction(1);
  double t_y_max = (box.max_corner(1) - ray.origin(1)) / ray.direction(1);
  double t_z_min = (box.min_corner(2) - ray.origin(2)) / ray.direction(2);
  double t_z_max = (box.max_corner(2) - ray.origin(2)) / ray.direction(2);

  double t_xyz_min = std::min( {t_x_min, t_y_min, t_z_min} );
  double t_xyz_max = std::max( {t_x_max, t_y_max, t_z_max} );
  
  // Intersect if either t_xyz_min or t_xyz_max within range min_t to max_t
  if ( (min_t < t_xyz_min && t_xyz_min < max_t) || 
       (min_t < t_xyz_max && t_xyz_max < max_t) )
    return true;

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
