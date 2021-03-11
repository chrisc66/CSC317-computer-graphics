// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // blinn_phong argument p
  float p = 1000.0;
  // blinn_phong argument n
  vec3 n = normalize(normal_fs_in);
  // blinn_phong argument v
  vec3 v = - normalize(view_pos_fs_in).xyz;
  // blinn_phong argument l
  float theta = 2 * M_PI * animation_seconds / 4;
  vec4 light = view * vec4(2 * cos(theta), 1.5, 2 * sin(theta), 1);
  vec3 l = normalize(light - view_pos_fs_in).xyz;

  if (is_moon){
    vec3 ka = vec3(0.03, 0.03, 0.09);
    vec3 kd = vec3(0.5,  0.5,  0.5);
    vec3 ks = vec3(0.8,  0.8,  0.8);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  else {
    vec3 ka = vec3(0.03, 0.03, 0.09);
    vec3 kd = vec3(0.3,  0.3,  0.9);
    vec3 ks = vec3(0.8,  0.8,  0.8);
    color = blinn_phong(ka, kd, ks, p, n, v, l);
  }
  /////////////////////////////////////////////////////////////////////////////
}
