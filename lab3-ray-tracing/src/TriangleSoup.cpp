#include "TriangleSoup.h"
#include "Triangle.h"
#include "first_hit.h"
bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Find first hit in all triangles within the TriangleSoup
  int id = -1;
  return first_hit(ray, min_t, triangles, id, t, n);
  ////////////////////////////////////////////////////////////////////////////
}
