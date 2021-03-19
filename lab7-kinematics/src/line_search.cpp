#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  double sigma = max_step;  // initialize to max_step
  
  Eigen::VectorXd delta_z = z - max_step * dz;  // z value after one gradient descent step
  proj_z(delta_z);

  double base_energy = f(z);
  double delta_energy = f(delta_z); // energy value after one gradient descent step
  
  while (delta_energy > base_energy){
      sigma = sigma / 2;
      delta_z = z - sigma * dz;
      proj_z(delta_z);
      delta_energy = f(delta_z);
  }

  return sigma;
  /////////////////////////////////////////////////////////////////////////////
}
