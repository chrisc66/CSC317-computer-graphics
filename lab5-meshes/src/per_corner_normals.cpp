#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  double pi = atan(1) * 4; // pi = 3.14...

  // Get triangle mesh adjacency information VF
  std::vector< std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  Eigen::RowVector3d a;
  Eigen::RowVector3d b;
  Eigen::RowVector3d c;
  Eigen::RowVector3d n;

  // face 
  Eigen::RowVector3d f_a;
  Eigen::RowVector3d f_b;
  Eigen::RowVector3d f_c;
  Eigen::RowVector3d f_n;

  int n_idx = 0;  // N vector index
  int p_idx = 0;  // point index
  int f_idx = 0;  // face index
  
  // Traverse through each rows and columns in face vector F
  for (int i = 0; i < F.rows(); i ++){
    
    // find normal vector n
    a = V.row(F(i,0));
    b = V.row(F(i,1));
    c = V.row(F(i,2));
    n = triangle_area_normal(a,b,c);
    
    for (int j = 0; j < F.cols(); j ++){
      
      n_idx = 3 * i + j;
      p_idx = F(i,j);

      // Traverse through each elements in VF at current point
      for (int k = 0; k < VF[p_idx].size(); k ++){
        
        // find normal vector at current face
        f_idx = VF[p_idx][k];
        f_a = V.row(F(f_idx,0));
        f_b = V.row(F(f_idx,1));
        f_c = V.row(F(f_idx,2));
        f_n = triangle_area_normal(f_a, f_b, f_c);
        
        if (f_n.dot(n) / (f_n.norm() * n.norm()) > cos(corner_threshold * pi / 180.0)){
          N(n_idx,0) = N(n_idx,0) + f_n(0);
          N(n_idx,1) = N(n_idx,1) + f_n(1);
          N(n_idx,2) = N(n_idx,2) + f_n(2);
        }
      }
      
      N.row(n_idx).normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
