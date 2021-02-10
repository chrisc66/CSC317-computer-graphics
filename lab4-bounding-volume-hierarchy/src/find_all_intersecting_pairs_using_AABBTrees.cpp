#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  
  // Create a linked list that each element contains a pair of AABBTree nodes
  std::list< std::pair <std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree> > > list;
  
  // Temporary variables for objects and tree nodes
  std::shared_ptr<AABBTree> tmp_nodeA;
  std::shared_ptr<AABBTree> tmp_nodeB;

  // Insert the first node pair (rootA, rootB) into list
  if (box_box_intersect(rootA->box, rootB->box))
    list.emplace_back( rootA, rootB );

  // Using list as a queue structure
  // Dynamically increase or shrink the list to traverse through tree A and B
  while (!list.empty()){
    
    // record front of the list / queue
    tmp_nodeA = list.front().first;
    tmp_nodeB = list.front().second;
    list.pop_front();
    
    // Node A & B both leaf node
    // Check for intersection between nodeA box with nodeB boxes
    // Insert current pair into leaf_pairs
    if (tmp_nodeA->num_leaves <= 1 && tmp_nodeB->num_leaves <= 1){
      if (box_box_intersect(tmp_nodeA->left->box, tmp_nodeB->left->box))
        leaf_pairs.emplace_back( tmp_nodeA->left, tmp_nodeB->left);
    }
    
    // Node A leaf node, node B intermediate node
    // Check for intersection between nodeA box with nodeB (left and right) boxes
    else if (tmp_nodeA->num_leaves <= 1 && tmp_nodeB->num_leaves > 1){
      if (box_box_intersect(tmp_nodeA->box, tmp_nodeB->left->box))
        list.emplace_back( tmp_nodeA, std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->left)) ;
      if (box_box_intersect(rootA->box, rootB->right->box))
        list.emplace_back( tmp_nodeA, std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->right) );
    }
    
    // Node A intermediate node, node B leaf node
    // Check for intersection between nodeA (left and right) boxes with nodeB box
    else if (tmp_nodeA->num_leaves > 1 && tmp_nodeB->num_leaves <= 1){
      if (box_box_intersect(tmp_nodeA->left->box, tmp_nodeB->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->left), tmp_nodeB );
      if (box_box_intersect(tmp_nodeA->right->box, tmp_nodeB->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->right), tmp_nodeB );
    }
    
    // Node A & B both intermediate node
    // Check for intersection between nodeA (left and right) boxes with nodeB (left and right) boxes
    else {
      if (box_box_intersect(tmp_nodeA->left->box, tmp_nodeB->left->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->left), std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->left) );
      if (box_box_intersect(tmp_nodeA->left->box, tmp_nodeB->right->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->left), std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->right) );
      if (box_box_intersect(tmp_nodeA->right->box, tmp_nodeB->left->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->right), std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->left) );
      if (box_box_intersect(tmp_nodeA->right->box, tmp_nodeB->right->box))
        list.emplace_back( std::dynamic_pointer_cast<AABBTree>(tmp_nodeA->right), std::dynamic_pointer_cast<AABBTree>(tmp_nodeB->right) );
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
