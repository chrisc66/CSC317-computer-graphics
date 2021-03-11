// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // mix — linearly interpolate between two values
  // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/mix.xhtml
  vec3 i = floor(st);
  vec3 f = fract(st);
  vec3 u = smooth_step(f);

  // generate x noises 
  float x1 = mix(dot(random_direction(i + vec3(0.0,1.0,0.0)), f - vec3(0.0,1.0,0.0)),
                 dot(random_direction(i + vec3(1.0,1.0,0.0)), f - vec3(1.0,1.0,0.0)), 
                 u.x);
  float x2 = mix(dot(random_direction(i + vec3(0.0,0.0,0.0)), f - vec3(0.0,0.0,0.0)),
                 dot(random_direction(i + vec3(1.0,0.0,0.0)), f - vec3(1.0,0.0,0.0)), 
                 u.x);
  float x3 = mix(dot(random_direction(i + vec3(0.0,0.0,1.0)), f - vec3(0.0,0.0,1.0)),
                 dot(random_direction(i + vec3(1.0,0.0,1.0)), f - vec3(1.0,0.0,1.0)), 
                 u.x);
  float x4 = mix(dot(random_direction(i + vec3(0.0,1.0,1.0)), f - vec3(0.0,1.0,1.0)),
                 dot(random_direction(i + vec3(1.0,1.0,1.0)), f - vec3(1.0,1.0,1.0)), 
                 u.x);
  // generate y noises
  float y1 = mix(x1, x2, u.y);
  float y2 = mix(x3, x4, u.y);
  // generate z noise (final noise value)
  float z = mix(y1, y2, u.z);

  return z;
  /////////////////////////////////////////////////////////////////////////////
}

