#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  int num_v = (num_faces_v + 1) * (num_faces_u + 1);
  int num_f = num_faces_v * num_faces_u;

  V.resize(num_v,3);
  F.resize(num_f,4);
  UV.resize(num_v,2);
  UF.resize(num_f,4);
  NV.resize(num_v,3);
  NF.resize(num_f,4);

  // Calculate delta u, v, 2D u, 2D v
  double pi = atan(1) * 4; // pi = 3.14...
  double du = 2 * pi / num_faces_u;
  double dv = pi / num_faces_v;

  int idx = 0;

  // traverse through every longtitude and latitude index
  for (int i = 0; i < num_faces_v + 1; i ++){
    for (int j = 0; j < num_faces_u + 1; j ++){

      // Index of current quad
      idx = i * num_faces_u + j;

      // Conversion between spherical and cartesian coordinate system 
      // V size: num_v * 3
      V(idx, 0) = cos(j*du) * sin(i*dv);  // x
      V(idx, 1) = sin(j*du) * sin(i*dv);  // y
      V(idx, 2) = cos(i*dv);              // z
      
      // UV size: num_v * 2
      UV(idx, 0) = j / (double) num_faces_u;
      UV(idx, 1) = 1 - i / (double) num_faces_v;

      // NV size: num_v * 3
      NV(idx, 0) = 0.5 * (cos(j*du) * sin(i*dv) + cos((j+1)*du) * sin(i*dv));
      NV(idx, 1) = 0.5 * (sin(j*du) * sin(i*dv) + sin((j+1)*du) * sin(i*dv));
      NV(idx, 2) = 0.5 * (cos(i*dv) + cos((i+1)*du));

      // Handling corner cases at 0 / 360 degree
      if (j + 1 == num_faces_u){
        if (i + 1 == num_faces_v){
          F(idx, 0) = i * num_faces_u + j + 1;
          F(idx, 1) = (i + 1) * num_faces_u + j + 1;
          F(idx, 2) = (i + 1) * num_faces_u + 1;
          F(idx, 3) = i * num_faces_u + 1;
          
          UF(idx, 0) = i * num_faces_u + j + 1;
          UF(idx, 1) = (i + 1) * num_faces_u + j + 1;
          UF(idx, 2) = (i + 1) * num_faces_u + 1;
          UF(idx, 3) = i * num_faces_u + 1;
        }
        else {
          F(idx, 0) = i * num_faces_u + j + 1;
          F(idx, 1) = (i + 1) * num_faces_u + j + 1;
          F(idx, 2) = (i + 1) * num_faces_u + 2;
          F(idx, 3) = i * num_faces_u + 2;
          
          UF(idx, 0) = i * num_faces_u + j + 1;
          UF(idx, 1) = (i + 1) * num_faces_u + j + 1;
          UF(idx, 2) = (i + 1) * num_faces_u + 2;
          UF(idx, 3) = i * num_faces_u + 2;
        }

        NF(idx, 0) = i * num_faces_u + j + 1;
        NF(idx, 1) = i * num_faces_u + j + 1;
        NF(idx, 2) = i * num_faces_u + j + 1;
        NF(idx, 3) = i * num_faces_u + j + 1;
      }

      // General case
      else if (j < num_faces_u && i < num_faces_v){
        F(idx, 0) = i * num_faces_u + j + 1;
        F(idx, 1) = (i + 1) * num_faces_u + j + 1;
        F(idx, 2) = (i + 1) * num_faces_u + j + 2;
        F(idx, 3) = i * num_faces_u + j + 2;

        UF(idx, 0) = i * num_faces_u + j + 1;
        UF(idx, 1) = (i + 1) * num_faces_u + j + 1;
        UF(idx, 2) = (i + 1) * num_faces_u + j + 2;
        UF(idx, 3) = i * num_faces_u + j + 2;
        
        NF(idx, 0) = i * num_faces_u + j + 1;
        NF(idx, 1) = i * num_faces_u + j + 1;
        NF(idx, 2) = i * num_faces_u + j + 1;
        NF(idx, 3) = i * num_faces_u + j + 1;
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
