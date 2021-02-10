#include "triangle_triangle_intersection.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  // find max and min x,y,z values triangle A and B 
  double a_min_x = std::min({ A0(0), A1(0), A2(0) });
  double a_max_x = std::max({ A0(0), A1(0), A2(0) });
  double a_min_y = std::min({ A0(1), A1(1), A2(1) });
  double a_max_y = std::max({ A0(1), A1(1), A2(1) });
  double a_min_z = std::min({ A0(2), A1(2), A2(2) });
  double a_max_z = std::max({ A0(2), A1(2), A2(2) });

  double b_min_x = std::min({ B0(0), B1(0), B2(0) });
  double b_max_x = std::max({ B0(0), B1(0), B2(0) });
  double b_min_y = std::min({ B0(1), B1(1), B2(1) });
  double b_max_y = std::max({ B0(1), B1(1), B2(1) });
  double b_min_z = std::min({ B0(2), B1(2), B2(2) });
  double b_max_z = std::max({ B0(2), B1(2), B2(2) });

  // any overlap indicates intersection
  if (a_min_x <= b_max_x && b_min_x <= a_max_x &&
      a_min_y <= b_max_y && b_min_y <= a_max_y &&
      a_min_z <= b_max_z && b_min_z <= a_max_z)
		return true;
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
