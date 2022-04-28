#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>

template <typename T>
class AVLTree {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    int bias;
  };

  Node* root;

 public:
  AVLTree() : root(NULL){};

  AVLTree(const AVLTree& src) : root(NULL) { *this = src; };

  ~AVLTree(){
      // delete node;
  };

  AVLTree& operator=(const AVLTree& rhs) {
    if (this != &rhs) {
      // copy Node;
    }
    return *this;
  }
};

#endif /* ********************************************************* AVLTREE_H \
        */