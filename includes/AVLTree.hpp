#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

namespace ft {

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

  void addNode(const T& value) {
    if (compare(value)) {
      if (right)
        right->addNode(value);
      else
        right = new Node(value);
    } else {
      if (left)
        left->addNode(value);
      else
        left = new Node(value);
    }
  }

  void printTree() {
    if (left) left->printTree();
    std::cout << "data: " << data << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "bias: " << bias << std::endl;
    if (left) std::cout << "left: " << left->data << std::endl;
    if (right) std::cout << "right: " << right->data << std::endl;
    if (parent) std::cout << "parent: " << parent->data << std::endl;
    std::cout << "-----------------------------------" << std::endl;
    if (right) right->printTree();
  }

  bool compare(const T& value) {
    if (data < value) return true;
    return false;
  }
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

  void addNode(const T value) {
    if (!root)
      root = new Node(value);
    else
      root->addNode(value);
  }

  void printTree() {
    if (!root) {
      std::cout << "root is NULL." << std::endl;
    } else {
      std::cout << "-----------------------------------" << std::endl;
      root->printTree();
    }
  }
};

}  // namespace ft

#endif /* ********************************************************* AVLTREE_H \
        */