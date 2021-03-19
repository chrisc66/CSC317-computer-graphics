// Filter an input value to perform an even smoother step. This function should
// be a quintic polynomial with improved_smooth_step(0) = 0,
// improved_smooth_step(1) = 1, and zero first _and_ second derivatives at f=0
// and f=1. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   f  input value
// Returns filtered output value
float improved_smooth_step( float f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  // 6x^5 - 15x^4 + 10x^3 
  if (f >= 1)
    return 1;
  else if (f <= 0)
    return 0;
  else
    return 6 * pow(f, 5) - 15 * pow(f, 4) + 10 * pow(f, 3);
  /////////////////////////////////////////////////////////////////////////////
}
vec3 improved_smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  return vec3(improved_smooth_step(f.x), improved_smooth_step(f.y), improved_smooth_step(f.z));
  /////////////////////////////////////////////////////////////////////////////
}
