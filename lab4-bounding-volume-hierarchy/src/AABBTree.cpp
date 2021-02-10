#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // less than two objects
  if (objects.size() <= 1){
    insert_box_into_box(objects[0]->box, box);
    left = objects[0];
    right = nullptr;
    return;
  }

  int num_objects = objects.size();

  // insert each object box into current (top) box
  for (int i = 0; i < num_objects; i ++)
    insert_box_into_box(objects[i]->box, box);

  // box size on x, y, z axis
  double x_len = box.max_corner(0) - box.min_corner(0);
  double y_len = box.max_corner(1) - box.min_corner(1);
  double z_len = box.max_corner(2) - box.min_corner(2);
  double max_len = std::max({ x_len, y_len, z_len });

  std::vector< std::shared_ptr<Object> > left_objs;
  std::vector< std::shared_ptr<Object> > right_objs;

  // insert objects into either left or right
  for (int i = 0; i < num_objects; i ++){
    if (max_len == x_len){
      if (objects[i]->box.center()(0) <= box.center()(0))
        left_objs.push_back(objects[i]);
      else 
        right_objs.push_back(objects[i]);
    }
    else if (max_len == y_len){
      if (objects[i]->box.center()(1) <= box.center()(1))
        left_objs.push_back(objects[i]);
      else 
        right_objs.push_back(objects[i]);
    }
    else if (max_len == z_len){
      if (objects[i]->box.center()(2) <= box.center()(2))
        left_objs.push_back(objects[i]);
      else 
        right_objs.push_back(objects[i]);
    }
  }

  // ensure that left and right are balanced
  if (left_objs.size() == 0 && right_objs.size() >= 2) {
    left_objs.push_back(right_objs.back());
    right_objs.pop_back();
  }
  if (right_objs.size() == 0 && left_objs.size() >= 2) {
    right_objs.push_back(left_objs.back());
    left_objs.pop_back();
  }

  // recursive calling constructor
  left = std::make_shared<AABBTree>(left_objs, depth+1);
  right = std::make_shared<AABBTree>(right_objs, depth+1);
  ////////////////////////////////////////////////////////////////////////////
}
