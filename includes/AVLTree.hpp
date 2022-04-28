#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

#define RIGHT true
#define LEFT false

namespace ft {

template <typename T>
struct Node {
  T data;
  Node* left;
  Node* right;
  Node* parent;
  int height;
  int bias;

  Node(const T& value = T(), Node* parent = NULL)
      : data(value),
        left(NULL),
        right(NULL),
        parent(parent),
        height(1),
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
    Node** target = compare(value) ? &right : &left;
    if (*target)
      (*target)->addNode(value);
    else
      (*target) = new Node(value, this);
    calcHeightAndBias();
    rotate();
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

  void printTreeGraph() {
    if (left) left->printTreeGraph();
    std::cout << data << " [label=\"" << data << "\nbias: " << bias
              << "\nheight: " << height << "\"]" << std::endl;
    if (left) {
      std::cout << data << "->" << left->data << " [color = blue];"
                << std::endl;
    }
    if (right) {
      std::cout << data << "->" << right->data << " [color = red];"
                << std::endl;
    }
    if (right) right->printTreeGraph();
  }

  bool compare(const T& value) {
    if (data < value) return true;
    return false;
  }

  void calcHeightAndBias() {
    int right_h = right ? right->height : 0;
    int left_h = left ? left->height : 0;
    height = 1;

    height += left_h > right_h ? left_h : right_h;
    bias = left_h - right_h;
  }

  void joinNode(Node* parent, bool is_right_child, Node* child) {
    if (is_right_child) {
      parent->right = child;
    } else {
      parent->left = child;
    }
    if (child) {
      child->parent = parent;
    }
  }

  void rotate() {
    if (bias > 1) {
      rotateR();
    } else if (bias < -1) {
      rotateL();
    }
  }

  void rotateL() {
    Node* pivot = right;
    Node* old_parent = parent;
    bool is_right_child = this->parent->right == this ? true : false;

    joinNode(this, RIGHT, pivot->left);
    joinNode(pivot, LEFT, this);
    joinNode(old_parent, is_right_child, pivot);
    this->calcHeightAndBias();
    pivot->calcHeightAndBias();
    old_parent->calcHeightAndBias();
  }

  void rotateR() {
    Node* pivot = left;
    Node* old_parent = parent;
    bool is_right_child = this->parent->right == this ? true : false;

    joinNode(this, LEFT, pivot->right);
    joinNode(pivot, RIGHT, this);
    joinNode(old_parent, is_right_child, pivot);
    this->calcHeightAndBias();
    pivot->calcHeightAndBias();
    old_parent->calcHeightAndBias();
  }
};

template <typename T>
class AVLTree {
 private:
  typedef Node<T> Node;
  Node*& root;
  Node end;

 public:
  AVLTree() : root(end.left){};

  AVLTree(const AVLTree& src) : root(end.left) { *this = src; };

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
    if (!root) {
      root = new Node(value, &end);
    }

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

  void printTreeGraph() {
    if (!root) {
      std::cout << "root is NULL." << std::endl;
    } else {
      std::cout << "digraph sample {" << std::endl;
      root->printTreeGraph();
      std::cout << "}" << std::endl;
    }
  }
};

}  // namespace ft

#endif /* ********************************************************* AVLTREE_H \
        */