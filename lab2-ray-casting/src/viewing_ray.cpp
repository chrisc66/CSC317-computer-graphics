#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Equations reference lecture2 slides p28-29
  // position vector (U, V) lengths / norms at pixel (i, j)
  double u = camera.width * (j + 0.5) / width - camera.width / 2;
  double v = - camera.height * (i + 0.5) / height + camera.height / 2;
  // Constructing ray origin and direction in vector forms
  ray.origin = camera.e;
  ray.direction = - camera.w * camera.d + camera.u * u + camera.v * v;
  ////////////////////////////////////////////////////////////////////////////
}

