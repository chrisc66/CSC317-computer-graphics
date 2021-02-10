#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <limits>// std::numeric_limits<double>::infinity();

// define distance-object pair (dist_obj_pair) that contains distance and object pointer
typedef std::pair<double, std::shared_ptr<Object> > dist_obj_pair;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  bool hit = false;
  sqrd = std::numeric_limits<double>::infinity();

  // Create min heap that contains distance-object pairs
  std::priority_queue< dist_obj_pair, std::vector<dist_obj_pair>, std::greater<dist_obj_pair> > queue; 

  // Insert the first distance-object pair (AABB root) into min heap
  // pair (distance, aabb node)
  queue.push(dist_obj_pair( point_box_squared_distance(query, root->box), root ));

  // Temporary variables to record heap information
  dist_obj_pair tmp_top;
  std::shared_ptr<AABBTree> tmp_node;
  double tmp_dist;

  // Dynamically increase or shrink the heap to traverse through the AABBTree
  while(!queue.empty()){

    // record top of the heap
    tmp_top = queue.top();
    queue.pop();

    // distance from top box is less than minimum distance
    if (tmp_top.first < sqrd){

      // dynamic pointer cast check to convert top object to aabb tree
      tmp_node = std::dynamic_pointer_cast<AABBTree>(tmp_top.second);

      // check success: intermediate tree node 
      if (tmp_node != nullptr){
        if (tmp_node->left != nullptr)
          queue.push(dist_obj_pair( point_box_squared_distance(query, tmp_node->left->box), tmp_node->left ));
        if (tmp_node->right != nullptr)
          queue.push(dist_obj_pair( point_box_squared_distance(query, tmp_node->right->box), tmp_node->right ));
      }
      
      // check failed: leaf node
      else {
        tmp_dist = point_box_squared_distance(query, tmp_top.second->box);
        // record smallest distance squared and descendant
        if (tmp_dist < sqrd){
          hit = true;
          sqrd = tmp_dist;
          descendant = tmp_top.second;
        }
      }
    }
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
