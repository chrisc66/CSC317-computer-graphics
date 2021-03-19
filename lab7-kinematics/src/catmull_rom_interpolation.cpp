#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  if (keyframes.empty()) {
      return Eigen::Vector3d::Zero();
  }

  t = fmod(t, keyframes.back().first);

  for (int i = 0; i < keyframes.size(); i ++){
    if (t <= keyframes[i].first){
      double temp_t = (t-keyframes[fmax(i-1,0)].first)/(keyframes[i].first-keyframes[fmax(i-1,0)].first);
      Eigen::MatrixXd poly_t(1,4); //t^0, t^1, t^2, t^3
      poly_t.row(0) = Eigen::Vector4d(pow(temp_t,0), pow(temp_t,1), pow(temp_t,2), pow(temp_t,3));

      Eigen::MatrixXd M(4,4); 
      M.row(0) = Eigen::Vector4d( 1,  0,  0,  0);
      M.row(1) = Eigen::Vector4d( 0,  0,  1,  0);
      M.row(2) = Eigen::Vector4d(-3,  3, -2, -1);
      M.row(3) = Eigen::Vector4d( 2, -2,  1,  1);
      
      Eigen::MatrixXd p_vector(4,3); // p0, p1, p0',p1'
      p_vector.row(0) = keyframes[fmax(i-1,0)].second;
      p_vector.row(2) = 0.5 * (keyframes[fmax(i-2,0)].second - keyframes[i].second);
      p_vector.row(1) = keyframes[i].second;
      p_vector.row(3) = 0.5*(keyframes[fmin(i+1,keyframes.size())].second - keyframes[fmax(i-1,0)].second);
      
      return (poly_t * M * p_vector).transpose();
    }
  }
  
  return Eigen::Vector3d::Zero();
  /////////////////////////////////////////////////////////////////////////////
}
