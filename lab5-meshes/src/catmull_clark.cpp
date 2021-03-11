#include "catmull_clark.h"
#include "vertex_triangle_adjacency.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  // Base case: do nothing if num_iters = 0
  if (num_iters == 0){
    return;
  }

  // General case: calculate catmull clark
  else {
	// Commenting this section out, got stuck in Step 2
	// Finished step 1, 
	// Pseudo code are written for step 2-5
	/*******************************************************************
	// Initialize SV & SF
	SV = V;
	SF.resize(F.rows() * 4, 4);

	// Step 1: Get center point of each face
	// Face Center Matrix, stores the center of each face
	Eigen::MatrixXi FC = Eigen::MatrixXi::Zero(F.rows(),1);
	// traverse through every face in Face Matrix	
	for (int i = 0; i < F.rows(); i ++) {
	  // get face corners
      Eigen::Vector3d face_a, face_b, face_c, face_d;
	  for (int j = 0; j < 3; j ++) {
		face_a(j) = SV(F(i, 0), j);
		face_b(j) = SV(F(i, 1), j);
		face_c(j) = SV(F(i, 2), j);
		face_d(j) = SV(F(i, 3), j);
	  }
	  // calculate face center
	  Eigen::Vector3d face_center;
      face_center(0) = (face_a(0) + face_b(0) + face_c(0) + face_d(0)) / 4;
	  face_center(1) = (face_a(1) + face_b(1) + face_c(1) + face_d(1)) / 4;
	  face_center(2) = (face_a(2) + face_b(2) + face_c(2) + face_d(2)) / 4;
	  // append face center to that last row of SV vertex positions 
	  int fc_idx = SV.rows();
	  SV.conservativeResize(fc_idx+1, 3);
	  SV(fc_idx, 0) = face_center(0);
	  SV(fc_idx, 1) = face_center(1);
	  SV(fc_idx, 2) = face_center(2);
	  // add face center idx to Face Center Matrix
	  FC(i,0) = fc_idx;
    }

	// Step 2: Get center point of each edge
	// Find adjacent verteces
	std::vector< std::vector<int> > VF;
	vertex_triangle_adjacency(F, V.rows(), VF);
	// Edge Center (EC) Matrix, stores the center of each face
	Eigen::MatrixXi EC = Eigen::MatrixXi::Zero(F.rows(),1);
	// traverse through every edge of every face using two for loops
	for (int i = 0; i < F.rows(); i ++){
	  for (int j = 0; j < 4; j ++){
		// find neighbouring faces and the edge in between
		// verify the edge isn't calculated before
		// find center of the edge
		// store center in to Edge Center (EC) Matrix
	  }
	}

	// Step 3: Add edges between face center and edge center points

	// Step 4: move origin vertex
	// new SV = ( F + 2R + (n-3) * P ) / n

	// Step 5: Connect points and create new meshes
	// new SF = connect four corner vertices 

  *******************************************************************/
  }

  // Recursive call: with temp SV and SF values
  Eigen::MatrixXd old_V = SV;
  Eigen::MatrixXi old_F = SF;
  catmull_clark(old_V, old_F, num_iters-1, SV, SF);

  return;
}
