#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  // Calculate the difference between Amax and Bmin
  Eigen::RowVector3d diff_ab = A.max_corner - B.min_corner;
  // Calculate the difference between Amin and Bmax
  Eigen::RowVector3d diff_ba = B.max_corner - A.min_corner;

  // Intersect if both difference are positive (overlap)
  if (diff_ab(0) >= 0 && diff_ab(1) >= 0 && diff_ab(2) >= 0 && 
      diff_ba(0) >= 0 && diff_ba(1) >= 0 && diff_ba(2) >= 0)
    return true;
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

