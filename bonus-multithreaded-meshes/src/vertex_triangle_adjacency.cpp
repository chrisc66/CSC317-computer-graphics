#include "vertex_triangle_adjacency.h"
#include <vector>

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  VF.resize(num_vertices);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // Clear VF vector and insert all i value (F.rows) into VF
  int vf_idx = 0;

  // Traverse through all F elements
  for (int i = 0; i < F.rows(); i ++){
    for (int j = 0; j < F.cols(); j ++){
      VF[F.row(i)(j)].push_back(i);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

