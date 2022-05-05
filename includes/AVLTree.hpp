#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <cstddef>
#include <functional>
#include <iostream>

#include "iterator.hpp"
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

    explicit AVLNode(const Key& key, const T& value = T(),
                     AVLNode* parent = NULL)
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

 private:
  typedef AVLNode Node;
  typedef typename Allocator::template rebind<Node>::other NodeAllcator;

 public:
  template <class value>
  class tree_iterator
      : public iterator<std::bidirectional_iterator_tag, value> {
   private:
    typedef iterator<std::bidirectional_iterator_tag, value> iterator_type;

   public:
    typedef typename iterator_type::value_type value_type;
    typedef typename iterator_type::difference_type difference_type;
    typedef typename iterator_type::pointer pointer;
    typedef typename iterator_type::reference reference;
    typedef typename iterator_type::iterator_category iterator_category;

   private:
    Node* current_node_;

   public:
    tree_iterator() : current_node_(NULL){};
    explicit tree_iterator(Node* ptr) : current_node_(ptr) {}
    tree_iterator(const tree_iterator& src) { *this = src; };
    ~tree_iterator(){};
    tree_iterator& operator=(const tree_iterator& rhs) {
      if (this != &rhs) {
        current_node_ = rhs.current_node_;
      }
      return *this;
    }

    tree_iterator& operator++() {
      current_node_ = current_node_->getNextNode();
      return *this;
    }

    tree_iterator operator++(int) {
      tree_iterator tmp = *this;
      current_node_ = current_node_->getNextNode();
      return tmp;
    }

    tree_iterator& operator--() {
      current_node_ = current_node_->getPrevNode();
      return *this;
    }

    tree_iterator operator--(int) {
      tree_iterator tmp = *this;
      current_node_ = current_node_->getPrevNode();
      return tmp;
    }

    bool operator==(const tree_iterator& rhs) const {
      return current_node_ == rhs.current_node_;
    }

    bool operator!=(const tree_iterator& rhs) const {
      return current_node_ != rhs.current_node_;
    }

    reference operator*() const { return current_node_->data; }

    pointer operator->() const { return &(operator*()); };
  };

 private:
  typedef tree_iterator<value_type> iterator;
  typedef tree_iterator<const value_type> const_iterator;

 private:
  Node*& root;
  Node end;
  Node* end_ptr;
  NodeAllcator allocator;
  Compare comp;

 public:
  AVLTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
      : end(Node(Key())),
        end_ptr(&end),
        root(end.left),
        allocator(NodeAllcator(alloc)),
        comp(comp){};

  AVLTree(const AVLTree& src)
      : end(Node(Key())), end_ptr(&end), root(end.left) {
    *this = src;
  };

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
      allocator = rhs.allocator;
      comp = rhs.comp;

      Node* featured = rhs.root->getMinNode();

      while (featured != &(rhs.end)) {
        this->addNode(featured->data.first, featured->data.second);
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

  Node* addNode(const Key& key, const T& value) {
    if (!root) {
      root = allocateNode(key, value, &end);
      return root;
    }

    Node* featured = root;
    Node** target = NULL;
    while (1) {
      target = featured->getNextDirection(key);
      if (*target == NULL) break;
      featured = *target;
    }

    *target = allocateNode(key, value, featured);

    balanceNode(featured);
    return *target;
  }

  Node* findNode(const Key& key) const {
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

      Node* substitute_dst = allocateNode(*substitute_src);
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

  Node* allocateNode(const Key& key, const T& value = T(),
                     Node* parent = NULL) {
    Node* res = NULL;

    res = allocator.allocate(1);
    allocator.construct(res, key, value, parent);
    return res;
  }

  Node* allocateNode(const AVLNode& src) {
    Node* res = NULL;

    res = allocator.allocate(1);
    allocator.construct(res, src);
    return res;
  }

 public:
  pair<iterator, bool> insertNode(const value_type& pair) {
    Node* node = findNode(pair.first);
    if (node) {
      return make_pair(iterator(node), false);
    } else {
      Node* res = addNode(pair.first, pair.second);
      return make_pair(iterator(res), true);
    }
  }

  iterator getBeginIterator() {
    Node* node = root ? root->getMinNode() : NULL;
    return iterator(node);
  }

  const_iterator getBeginIterator() const {
    Node* node = root ? root->getMinNode() : NULL;
    return const_iterator(node);
  }

  iterator getEndIterator() { return iterator(end_ptr); }

  const_iterator getEndIterator() const { return const_iterator(end_ptr); }

  bool isEmpty() const { return root == NULL; }

  size_t size() const {
    size_t res = 0;
    if (!isEmpty()) res = root->size;
    return res;
  }

  typename NodeAllcator::size_type getMaxSize() const {
    return allocator.max_size();
  }

  iterator findData(const Key& key) const {
    Node* res = NULL;
    res = findNode(key);
    if (res == NULL)
      return iterator(end_ptr);
    else
      return iterator(res);
  }
};

}  // namespace ft

#endif /* ********************************************************* AVLTREE_H \
        */
