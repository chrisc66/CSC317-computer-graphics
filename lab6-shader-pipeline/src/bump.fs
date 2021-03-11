// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // Re-using lit.fs code with additional bumps

  // tangent & bump_height & bump_position
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  float epsilon = 0.0001;
  vec3 bump = bump_position(is_moon, sphere_fs_in);
  vec3 delta_t = (bump_position(is_moon, sphere_fs_in + epsilon * T) - bump) / epsilon;
  vec3 delta_b = (bump_position(is_moon, sphere_fs_in + epsilon * B) - bump) / epsilon;
  // blinn_phong argument n
  mat4 model = model(is_moon, animation_seconds / 4);
  vec3 delta_n = normalize(cross(delta_t, delta_b));
  vec3 n = normalize(transpose(inverse(view)) * transpose(inverse(model)) * vec4(delta_n,1)).xyz;
  // blinn_phong argument p
  float p = 1000.0;
  // blinn_phong argument v
  vec3 v = - normalize(view_pos_fs_in).xyz;
  // blinn_phong argument l
  float theta = 2 * M_PI * animation_seconds / 4;
  vec4 light = view * vec4(2*cos(theta), 1.5, 2*sin(theta), 1);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  if (is_moon){
    vec3 ka = vec3(0.1, 0.1, 0.1);
    vec3 kd = vec3(0.5, 0.5, 0.5);
    vec3 ks = vec3(0.8, 0.8, 0.8);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else {
    vec3 ka = vec3(0.07, 0.07, 0.21);
    vec3 kd = vec3(0.3,  0.3,  0.9 );
    vec3 ks = vec3(0.8,  0.8,  0.8 );
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
