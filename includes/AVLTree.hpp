#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

#include "pair.hpp"

#define RIGHT true
#define LEFT false

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<pair<const Key, T>>>
class AVLTree {
 private:
  typedef pair<const Key, T> value_type;

  struct AVLNode {
    value_type data;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;
    int bias;
    int size;

    AVLNode(const Key& key, const T& value = T(), AVLNode* parent = NULL)
        : data(value_type(key, value)),
          left(NULL),
          right(NULL),
          parent(parent),
          height(1),
          size(1),
          bias(0) {}

    AVLNode(const AVLNode& src) : data(value_type(src.data)) { *this = src; }

    ~AVLNode() {
      if (parent) {
        if (isRightChild()) {
          parent->right = NULL;
        } else {
          parent->left = NULL;
        }
      }
    }

    AVLNode& operator=(const AVLNode& rhs) {
      if (this != &rhs) {
        left = rhs.left;
        right = rhs.right;
        parent = rhs.parent;
        height = rhs.height;
        bias = rhs.bias;
        size = rhs.size;
      }
      return *this;
    }

    void printTreeGraph() {
      if (left) left->printTreeGraph();
      std::cout << data.first << " [label=\""
                << "key: " << data.first << "\nvalue: " << data.second << "\"]"
                << std::endl;
      if (left) {
        std::cout << data.first << "->" << left->data.first
                  << " [color = blue];" << std::endl;
      }
      if (right) {
        std::cout << data.first << "->" << right->data.first
                  << " [color = red];" << std::endl;
      }
      if (right) right->printTreeGraph();
    }

    bool compare(const Key& key) {
      if (Compare()(data.first, key)) return true;
      return false;
    }

    bool equal(const Key& key) {
      return !(compare(key)) && !(AVLNode(key).compare(data.first));
    }

    void updateNodeInfo() {
      int right_h = right ? right->height : 0;
      int left_h = left ? left->height : 0;
      height = 1;
      height += left_h > right_h ? left_h : right_h;
      bias = left_h - right_h;

      int right_s = right ? right->size : 0;
      int left_s = left ? left->size : 0;
      size = 1;
      size += right_s + left_s;
    }

    void joinNode(bool is_right_child, AVLNode* child) {
      if (is_right_child) {
        right = child;
      } else {
        left = child;
      }
      if (child) {
        child->parent = this;
      }
    }
    void substituteNode(AVLNode* src) {
      parent->joinNode(isRightChild(), src);
      src->joinNode(RIGHT, right);
      src->joinNode(LEFT, left);

      parent = NULL;
      right = NULL;
      left = NULL;
    }

    void rotate() {
      if (bias > 1) {
        if (left && left->bias <= -1) {
          left->rotateL();
          rotateR();
        } else {
          rotateR();
        }

      } else if (bias < -1) {
        if (right && right->bias >= 1) {
          right->rotateR();
          rotateL();
        } else {
          rotateL();
        }
      }
    }

    void rotateL() {
      AVLNode* pivot = right;
      AVLNode* old_parent = parent;
      bool is_right_child = isRightChild();

      this->joinNode(RIGHT, pivot->left);
      pivot->joinNode(LEFT, this);
      old_parent->joinNode(is_right_child, pivot);
      this->updateNodeInfo();
      pivot->updateNodeInfo();
      old_parent->updateNodeInfo();
    }

    void rotateR() {
      AVLNode* pivot = left;
      AVLNode* old_parent = parent;
      bool is_right_child = isRightChild();

      this->joinNode(LEFT, pivot->right);
      pivot->joinNode(RIGHT, this);
      old_parent->joinNode(is_right_child, pivot);
      this->updateNodeInfo();
      pivot->updateNodeInfo();
      old_parent->updateNodeInfo();
    }

    void updateNode() {
      updateNodeInfo();
      rotate();
    }

    AVLNode** getNextDirection(const Key& key) {
      return compare(key) ? &right : &left;
    }

    AVLNode* getMaxNode() {
      AVLNode* featured = this;
      while (featured->right) {
        featured = featured->right;
      }
      return featured;
    }

    AVLNode* getMinNode() {
      AVLNode* featured = this;
      while (featured->left) {
        featured = featured->left;
      }
      return featured;
    }

    AVLNode* getNextNode() {
      if (right) {
        return right->getMinNode();
      } else if (!isRightChild()) {
        return parent;
      }
      AVLNode* featured = parent;
      while (featured->isRightChild()) {
        featured = featured->parent;
      }
      return featured->parent;
    }

    AVLNode* getPrevNode() {
      if (left) {
        return left->getMaxNode();
      } else if (isRightChild()) {
        return parent;
      }
      AVLNode* featured = parent;
      while (featured->parent->parent && !(featured->isRightChild())) {
        featured = featured->parent;
      }
      return featured->parent;
    }

    bool isRightChild() { return this->parent->right == this ? true : false; }
  };

  typedef typename Allocator::template rebind<AVLNode>::other node_allocator;

 private:
  typedef AVLNode Node;
  Node*& root;
  Node end;

 public:
  AVLTree() : end(Node("end")), root(end.left){};

  AVLTree(const AVLTree& src) : root(end.left) { *this = src; };

  ~AVLTree() {
    if (root == NULL) return;

    Node* featured = root->getMinNode();
    while (featured != &end) {
      if (featured->left)
        featured = featured->left;
      else if (featured->right)
        featured = featured->right;
      else {
        Node* tmp = featured;
        featured = featured->parent;
        delete tmp;
      }
    }
  };

  AVLTree& operator=(const AVLTree& rhs) {
    if (this != &rhs) {
      Node* featured = rhs.root->getMinNode();

      while (featured != &(rhs.end)) {
        this->addNode(featured->data);
        featured = featured->getNextNode();
      }
    }
    return *this;
  }

  void balanceNode(Node* featured) {
    while (featured && featured != &end) {
      featured->updateNode();
      featured = featured->parent;
    }
  }

  void addNode(const Key& key, const T& value) {
    if (!root) {
      root = new Node(key, value, &end);
      return;
    }

    Node* featured = root;
    Node** target = NULL;
    while (1) {
      target = featured->getNextDirection(key);
      if (*target == NULL) break;
      featured = *target;
    }

    *target = new Node(key, value, featured);

    balanceNode(featured);
  }

  Node* findNode(const Key& key) {
    Node* featured = root;
    while (featured && !featured->equal(key)) {
      featured = *(featured->getNextDirection(key));
    }
    return featured;
  }

  void deleteNode(const Key& key) {
    Node* target = findNode(key);
    if (!target) return;

    Node* deleteTarget = target;
    Node* featured = target->parent;

    if (target->left) {
      Node* substitute_src = target->left->getMaxNode();

      Node* substitute_dst = new Node(*substitute_src);
      target->substituteNode(substitute_dst);

      featured = substitute_src->parent;
      substitute_src->parent->joinNode(substitute_src->isRightChild(),
                                       substitute_src->left);

      delete substitute_src;

    } else if (target->right) {
      target->parent->joinNode(target->isRightChild(), target->right);
      target->parent = NULL;
    }

    delete target;
    balanceNode(featured);
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