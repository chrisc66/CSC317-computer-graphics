// Input:
//   N  3D unit normal vector
// Outputs:
//   T  3D unit tangent vector
//   B  3D unit bitangent vector
void tangent(in vec3 N, out vec3 T, out vec3 B)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // Tangent vector, theta between x and z magnitude
  // Bi-tangent vector, B = N x T
  if (N.z != 0){
    float theta = atan(N.x,N.z);
    T = normalize(vec3(cos(theta), 0, -sin(theta)));
    B = normalize(vec3(cross(N, T)));
  }
  else {
    // handle corner case when z = 0, on xy-plane
    T = normalize(vec3(cross(vec3(1, 0, 0), N)));
    B = normalize(vec3(cross(N, T)));
  }
  /////////////////////////////////////////////////////////////////////////////
}
