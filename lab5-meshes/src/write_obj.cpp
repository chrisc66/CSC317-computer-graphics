#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // Open file and fstream
  std::ofstream file;
  file.open(filename);

  // V: 3D vertex positions
  file << "# List of geometric vertices, with (x, y, z [,w]) coordinates, w is optional and defaults to 1.0." << std::endl;
  for (int i = 0; i < V.rows(); i++)
    file << "v " << V.row(i) << std::endl;

  // UV: 2D parametrization positions
  file << "# List of texture coordinates, in (u, [,v ,w]) coordinates, these will vary between 0 and 1. v, w are optional and default to 0." << std::endl;
  for (int i = 0; i < UV.rows(); i++)
    file << "vt " << UV.row(i) << std::endl;

  // NV: 3D normal vectors
  file << "# List of vertex normals in (x,y,z) form; normals might not be unit vectors." << std::endl;
  for (int i = 0; i < NV.rows(); i++)
    file << "vn " << NV.row(i) << std::endl;

  // F: 3D faces
  file << "# Polygonal face element (see below)" << std::endl;
  for (int i = 0; i < F.rows(); i++){
    file << "f ";
    for (int j = 0; j < F.cols(); j++)
        file << F(i, j) << "/" << UF(i, j) << "/" << NF(i, j) << " ";
    file << std::endl;
  }

  file.close();
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
