// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  if (is_moon){
    color = vec3(0.5, 0.5, 0.5);   // r = 128, g = 128, b = 128
  }
  else {
    color = vec3(0, 0, 1);         // r = 0, g = 0, b = 255
  }
  /////////////////////////////////////////////////////////////////////////////
}
