#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double tmp_d = std::numeric_limits<double>::infinity();
  sqrD = std::numeric_limits<double>::infinity();
  I = -1;

  // Find smalles distance squared and index
  for (int i = 0; i < points.rows(); i ++){
    // distance^2 = (point - query)^2
    tmp_d = (points.row(i) - query).squaredNorm();
    if (tmp_d < sqrD){
      sqrD = tmp_d;
      I = i;
    }
  }
  return;
  ////////////////////////////////////////////////////////////////////////////
}
