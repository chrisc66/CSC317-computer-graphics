#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Take the outer layer of box A and box B
  Eigen::RowVector3d A_min = A.min_corner;
  Eigen::RowVector3d A_max = A.max_corner;
  Eigen::RowVector3d B_min = B.min_corner;
  Eigen::RowVector3d B_max = B.max_corner;

  B.min_corner(0) = std::min(A_min(0), B_min(0));
  B.max_corner(0) = std::max(A_max(0), B_max(0));
  B.min_corner(1) = std::min(A_min(1), B_min(1));
  B.max_corner(1) = std::max(A_max(1), B_max(1));
  B.min_corner(2) = std::min(A_min(2), B_min(2));
  B.max_corner(2) = std::max(A_max(2), B_max(2));
  
  return;
  ////////////////////////////////////////////////////////////////////////////
}

