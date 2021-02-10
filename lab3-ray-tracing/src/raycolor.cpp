#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  const int MAX_RECURSIVE_CALLS = 5;  // maximum recursive calls allowed
  const double MIN_T_TMP = 0.0001;     // min_t value for raycolor recursive call

  if (num_recursive_calls > MAX_RECURSIVE_CALLS)
    return false;

  // Varibles for first_hit
  int hit_id;
  double t;
  Eigen::Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);

  if (hit) {
    // find ray colour rgb using blinn_phong_shading
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);

    // Variables for raycolor
    Ray tmp_ray;
    tmp_ray.origin = ray.origin + t * ray.direction;
    tmp_ray.direction = reflect(ray.direction, n);
    Eigen::Vector3d tmp_rgb;
    if (raycolor(tmp_ray, MIN_T_TMP, objects, lights, num_recursive_calls + 1, tmp_rgb))
      // delta = mirror * ray 
      rgb = rgb + (objects[hit_id]->material->km.array() * tmp_rgb.array()).matrix();
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
