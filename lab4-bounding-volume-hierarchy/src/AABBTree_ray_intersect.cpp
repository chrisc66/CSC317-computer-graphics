#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;

  // One leaf in the tree
  if (num_leaves == 1){
    if (left->ray_intersect(ray, min_t, max_t, t, descendant)){
      descendant = this->left;
      hit = true;
    }
    return hit;
  }

  // Check ray intersect box on left and right nodes
  bool tmp_l_hit = ray_intersect_box(ray, left->box, min_t, max_t);
  bool tmp_r_hit = ray_intersect_box(ray, right->box, min_t, max_t);

  if (tmp_l_hit && tmp_r_hit){

    // Check ray intersect AABBTree, recursive call
    // Re-declare variables, notice scoles only within this block
    std::shared_ptr<Object> tmp_l_desc;
    std::shared_ptr<Object> tmp_r_desc;
    double tmp_l_t;
    double tmp_r_t;
    bool tmp_l_hit = this->left->ray_intersect(ray, min_t, max_t, tmp_l_t, tmp_l_desc);
    bool tmp_r_hit = this->right->ray_intersect(ray, min_t, max_t, tmp_r_t, tmp_r_desc);
    
    // both hit, compare t value and take smaller side
    if (tmp_l_hit && tmp_r_hit){
      hit = true;
      t = (tmp_l_t < tmp_r_t) ? tmp_l_t : tmp_r_t;
      descendant = (tmp_l_t < tmp_r_t) ? tmp_l_desc : tmp_r_desc;
    }
    // left hit, right not hit, take left 
    else if (tmp_l_hit && !tmp_r_hit){
      hit = true;
      t = tmp_l_t;
      descendant = tmp_l_desc;
    }
    // right hit, left not hit, take right
    else if (!tmp_l_hit && tmp_r_hit){
      hit = true;
      t = tmp_r_t;
      descendant = tmp_r_desc;
    }
    // both not hit, do nothing
    else {
      hit = false;
    }
  }

  else if (tmp_l_hit && !tmp_r_hit){
    hit = this->left->ray_intersect(ray, min_t, max_t, t, descendant);
  }

  else if (!tmp_l_hit && tmp_r_hit){
    hit = this->right->ray_intersect(ray, min_t, max_t, t, descendant);
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

