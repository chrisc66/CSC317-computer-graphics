#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include <vector>

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(V.rows(),3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  Eigen::RowVector3d a;
  Eigen::RowVector3d b;
  Eigen::RowVector3d c;

  // Traverse through each row in V or N
  for (int i = 0; i < V.rows(); i ++) {
    Eigen::RowVector3d n(0, 0, 0);
    for (int j = 0; j < F.rows(); j ++) {
      if ( (F(j, 0) == i) || (F(j, 1) == i) || (F(j,2) == i) ){
        a = V.row(F(j, 0));
        b = V.row(F(j, 1));
        c = V.row(F(j, 2));
        n = n + triangle_area_normal(a, b, c);
      }
    }
    N.row(i) = n.normalized();
  }

  return;
  ////////////////////////////////////////////////////////////////////////////
}
