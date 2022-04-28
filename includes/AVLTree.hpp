#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>

template <typename T>
struct Node {
  T data;
  Node* left;
  Node* right;
  Node* parent;
  int height;
  int bias;

  Node(const T& value = T())
      : data(value),
        left(NULL),
        right(NULL),
        parent(NULL),
        height(0),
        bias(0) {}

  Node(const Node& src) { *this = src; }

  ~Node() {}

  Node& operator=(const Node& rhs) {
    if (this != &rhs) {
      data = rhs.data;
      left = rhs.left;
      right = rhs.right;
      parent = rhs.parent;
      height = rhs.height;
      bias = rhs.bias;
    }
    return *this;
  }

  void printTree() {}
};

template <typename T>
class AVLTree {
 private:
  typedef Node<T> Node;
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