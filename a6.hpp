// File: a6.hpp
// Hussam
// Abdellatif
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A6_HPP
#define A6_HPP

#include <ostream>
#include "symbol.hpp"
#include <queue>
#include <iostream>
#include <vector>
#include<string>

// MAKE SURE TO UPDATE YOUR INFORMATION IN THE HEADER OF THIS FILE
// IMPLEMENT ALL REQUIRED FUNCTIONS BELOW
// YOU ARE NOT ALLOWED TO ALTER ANY INTERFACE
// INSIDE A FUNCTION YOU CAN DO WHATEVER YOU LIKE
class comp{
public:
bool operator() (const bnode<symbol>* lh, const bnode<symbol>* rh) {
    const symbol& lhs = lh->value;
    const symbol& rhs = rh->value;
    return ((lhs.count > rhs.count) || (!(rhs.count > lhs.count) && (lhs.value > rhs.value)));
}
};


// IMPLEMENT YOUR FUNCTION huffman_tree
template <typename Iter>
  bnode<symbol>* huffman_tree(Iter first, Iter last){

    std::priority_queue<bnode<symbol>*,std::vector<bnode<symbol>*>,comp>x;
    for(; first!=last;first++){
      bnode<symbol>* bn = new bnode<symbol>;
      bn->value = *first;
      x.push(bn);
    }
    while(!x.empty()){
      if(x.size() == 1){
        return x.top();
      }else{
        //pointers to the nodes that are on the heap
        bnode<symbol>* temp1;
        bnode<symbol>* temp2;
        //parent needs to be a pointer to node on the heap, so that we can push it to the prioirty queue
        bnode<symbol>* parent = new bnode<symbol>;
        temp1 = x.top();
        x.pop();
        temp2 = x.top();
        x.pop();
        parent->left = temp1;
        parent->right = temp2;
        //nodes coming out of the priority queue are already sorted, just need to add value to the parent node, the value will be picked lexicographically
        if(temp1->value.value < temp2->value.value){
          parent->value.value = temp1->value.value;
        }else{
          parent->value.value = temp2->value.value;
        }
        parent->value.count = temp1->value.count + temp2->value.count;
        x.push(parent);
      }
    }
      return nullptr;
}
//recursive print of huffman code (helper function)
void print_helper(std::ostream& os,bnode<symbol>* root, std::string code){
  //base case
  if(root == nullptr){
    return;
  }
  //its a leaf with charaacter needed to print
  if(root->left == nullptr && root->right == nullptr){
    os<<root->value.value<<" "<<code<<"\n";
    code = "";
  }
  //teaverese the tree from left and right and add to string based on traversal
  print_helper(os, root->left, code + "0");
  print_helper(os, root->right, code + "1");
}

// IMPLEMENT YOUR FUNCTION print_dictionary
void print_dictionary(std::ostream& os, bnode<symbol>* root){
  std::string x;
  print_helper(os,root,x);
}



// IMPLEMENT YOUR FUNCTION release_tree
void release_tree(bnode<symbol>* root){
  if(root == nullptr)return;
  release_tree(root->left);
  release_tree(root->right);
  delete root;

}

#endif // A6_HPP
