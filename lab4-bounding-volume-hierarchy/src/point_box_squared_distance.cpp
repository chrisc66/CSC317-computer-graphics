#include "point_box_squared_distance.h"
#include <algorithm>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  
  // Find max value as distance, there should be only one positive value in each comparison
  // 1st value: query smaller than min_corner -> min_corner - query
  // 2nd value: query greater than max_corner -> query - max_corner
  // 3rd value: query within box boundary -> 0
  double dis_x = std::max( {box.min_corner(0) - query(0), query(0) - box.max_corner(0), 0.0} );
  double dis_y = std::max( {box.min_corner(1) - query(1), query(1) - box.max_corner(1), 0.0} );
  double dis_z = std::max( {box.min_corner(2) - query(2), query(2) - box.max_corner(2), 0.0} );

  // Calculate squared distance before return
  return (pow(dis_x, 2) + pow(dis_y, 2) + pow(dis_z, 2));
  ////////////////////////////////////////////////////////////////////////////
}
