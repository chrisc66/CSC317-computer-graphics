#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Take the outer layer of box B and three triangle corners
  Eigen::RowVector3d B_min = B.min_corner;
  Eigen::RowVector3d B_max = B.max_corner;

  B.min_corner(0) = std::min( {B_min(0), a(0), b(0), c(0) });
  B.max_corner(0) = std::max( {B_max(0), a(0), b(0), c(0) });
  B.min_corner(1) = std::min( {B_min(1), a(1), b(1), c(1) });
  B.max_corner(1) = std::max( {B_max(1), a(1), b(1), c(1) });
  B.min_corner(2) = std::min( {B_min(2), a(2), b(2), c(2) });
  B.max_corner(2) = std::max( {B_max(2), a(2), b(2), c(2) });
  
  return;
  ////////////////////////////////////////////////////////////////////////////
}


