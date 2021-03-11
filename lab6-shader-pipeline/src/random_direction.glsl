// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  vec2 st = random2(seed);
  vec3 random_vector = vec3(
    sin(M_PI*st.x) * cos(2*M_PI*st.y),
    sin(M_PI*st.x) * sin(2*M_PI*st.y),
    cos(M_PI*st.x));
  return normalize(random_vector);
  /////////////////////////////////////////////////////////////////////////////
}
