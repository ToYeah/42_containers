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
          class Allocator = std::allocator<pair<const Key, T> > >
class AVLTree {
 private:
  typedef pair<const Key, T> value_type;

  struct AVLNode {
    value_type data_;
    AVLNode* left_;
    AVLNode* right_;
    AVLNode* parent_;
    size_t height_;
    size_t size_;
    int bias_;

    explicit AVLNode(const Key& key, const T& value = T(),
                     AVLNode* parent = NULL)
        : data_(value_type(key, value)),
          left_(NULL),
          right_(NULL),
          parent_(parent),
          height_(1),
          size_(1),
          bias_(0) {}

    AVLNode(const AVLNode& src) : data_(value_type(src.data_)) { *this = src; }

    ~AVLNode() {}

    AVLNode& operator=(const AVLNode& rhs) {
      if (this != &rhs) {
        left_ = rhs.left_;
        right_ = rhs.right_;
        parent_ = rhs.parent_;
        height_ = rhs.height_;
        bias_ = rhs.bias_;
        size_ = rhs.size_;
      }
      return *this;
    }

    bool compare(const Key& key) {
      if (Compare()(data_.first, key)) return true;
      return false;
    }

    bool equal(const Key& key) {
      return !(compare(key)) && !(AVLNode(key).compare(data_.first));
    }

    void updateNodeInfo() {
      int right_h = right_ ? right_->height_ : 0;
      int left_h = left_ ? left_->height_ : 0;
      height_ = 1;
      height_ += left_h > right_h ? left_h : right_h;
      bias_ = left_h - right_h;

      int right_s = right_ ? right_->size_ : 0;
      int left_s = left_ ? left_->size_ : 0;
      size_ = 1;
      size_ += right_s + left_s;
    }

    void joinNode(bool is_right_child, AVLNode* child) {
      if (is_right_child) {
        right_ = child;
      } else {
        left_ = child;
      }
      if (child) {
        child->parent_ = this;
      }
    }

    void rotate() {
      if (bias_ > 1) {
        if (left_ && left_->bias_ <= -1) {
          left_->rotateL();
          rotateR();
        } else {
          rotateR();
        }

      } else if (bias_ < -1) {
        if (right_ && right_->bias_ >= 1) {
          right_->rotateR();
          rotateL();
        } else {
          rotateL();
        }
      }
    }

    void rotateL() {
      AVLNode* pivot = right_;
      AVLNode* old_parent = parent_;
      bool is_right_child = isRightChild();

      this->joinNode(RIGHT, pivot->left_);
      pivot->joinNode(LEFT, this);
      old_parent->joinNode(is_right_child, pivot);
      this->updateNodeInfo();
      pivot->updateNodeInfo();
      old_parent->updateNodeInfo();
    }

    void rotateR() {
      AVLNode* pivot = left_;
      AVLNode* old_parent = parent_;
      bool is_right_child = isRightChild();

      this->joinNode(LEFT, pivot->right_);
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
      return compare(key) ? &right_ : &left_;
    }

    AVLNode* getMaxNode() {
      AVLNode* featured = this;
      while (featured->right_) {
        featured = featured->right_;
      }
      return featured;
    }

    AVLNode* getMinNode() {
      AVLNode* featured = this;
      while (featured->left_) {
        featured = featured->left_;
      }
      return featured;
    }

    AVLNode* getNextNode() {
      if (right_) {
        return right_->getMinNode();
      } else if (!isRightChild()) {
        return parent_;
      }
      AVLNode* featured = parent_;
      while (featured->isRightChild()) {
        featured = featured->parent_;
      }
      return featured->parent_;
    }

    AVLNode* getPrevNode() {
      if (left_) {
        return left_->getMaxNode();
      } else if (isRightChild()) {
        return parent_;
      }
      AVLNode* featured = parent_;
      while (featured->parent_->parent_ && !(featured->isRightChild())) {
        featured = featured->parent_;
      }
      return featured->parent_;
    }

    bool isRightChild() { return this->parent_->right_ == this ? true : false; }

#ifdef DEV
    void printTreeGraph() {
      if (left_) left_->printTreeGraph();
      std::cout << data_.first << " [label=\""
                << "key: " << data_.first << "\nvalue: " << data_.second
                << "\"]" << std::endl;
      if (left_) {
        std::cout << data_.first << "->" << left_->data_.first
                  << " [color = blue];" << std::endl;
      }
      if (right_) {
        std::cout << data_.first << "->" << right_->data_.first
                  << " [color = red];" << std::endl;
      }
      if (right_) right_->printTreeGraph();
    }
#endif
  };

 private:
  typedef AVLNode Node;
  typedef typename Allocator::template rebind<Node>::other NodeAllcator;

 public:
  class tree_iterator
      : public iterator<std::bidirectional_iterator_tag, value_type> {
   private:
    typedef iterator<std::bidirectional_iterator_tag, value_type> iterator_type;

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

    reference operator*() const { return current_node_->data_; }

    pointer operator->() const { return &(operator*()); };

    Node* baseNode() const { return current_node_; }
  };

  class const_tree_iterator
      : public iterator<std::bidirectional_iterator_tag, const value_type> {
   private:
    typedef iterator<std::bidirectional_iterator_tag, const value_type>
        iterator_type;

   public:
    typedef typename iterator_type::value_type value_type;
    typedef typename iterator_type::difference_type difference_type;
    typedef typename iterator_type::pointer pointer;
    typedef typename iterator_type::reference reference;
    typedef typename iterator_type::iterator_category iterator_category;

   private:
    Node* current_node_;

   public:
    const_tree_iterator() : current_node_(NULL){};
    explicit const_tree_iterator(Node* ptr) : current_node_(ptr){};
    const_tree_iterator(const tree_iterator& it)
        : current_node_(it.baseNode()){};
    const_tree_iterator(const const_tree_iterator& src) { *this = src; };
    ~const_tree_iterator(){};
    const_tree_iterator& operator=(const const_tree_iterator& rhs) {
      if (this != &rhs) {
        current_node_ = rhs.current_node_;
      }
      return *this;
    }

    const_tree_iterator& operator++() {
      current_node_ = current_node_->getNextNode();
      return *this;
    }

    const_tree_iterator operator++(int) {
      const_tree_iterator tmp = *this;
      current_node_ = current_node_->getNextNode();
      return tmp;
    }

    const_tree_iterator& operator--() {
      current_node_ = current_node_->getPrevNode();
      return *this;
    }

    const_tree_iterator operator--(int) {
      const_tree_iterator tmp = *this;
      current_node_ = current_node_->getPrevNode();
      return tmp;
    }

    bool operator==(const const_tree_iterator& rhs) const {
      return current_node_ == rhs.current_node_;
    }

    bool operator!=(const const_tree_iterator& rhs) const {
      return current_node_ != rhs.current_node_;
    }

    reference operator*() const { return current_node_->data_; }

    pointer operator->() const { return &(operator*()); };

    Node* baseNode() const { return current_node_; }
  };

 private:
  typedef tree_iterator iterator;
  typedef const_tree_iterator const_iterator;

 private:
  Node end_;
  Node* end_ptr_;
  Node*& root_;
  NodeAllcator allocator_;
  Compare comp_;

 public:
  AVLTree(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
      : end_(Node(Key())),
        end_ptr_(&end_),
        root_(end_.left_),
        allocator_(NodeAllcator(alloc)),
        comp_(comp){};

  AVLTree(const AVLTree& src)
      : end_(Node(Key())), end_ptr_(&end_), root_(end_.left_) {
    *this = src;
  };

  ~AVLTree() { clearTree(); };

  AVLTree& operator=(const AVLTree& rhs) {
    if (this != &rhs) {
      allocator_ = rhs.allocator_;
      comp_ = rhs.comp_;

      clearTree();

      Node* featured = rhs.root_->getMinNode();

      while (featured != &(rhs.end_)) {
        this->addNode(featured->data_.first, featured->data_.second);
        featured = featured->getNextNode();
      }
    }
    return *this;
  }

  Node* findNode(const Key& key) const {
    Node* featured = root_;
    while (featured && !featured->equal(key)) {
      featured = *(featured->getNextDirection(key));
    }
    return featured;
  }

  pair<iterator, bool> insertNode(const value_type& pair) {
    Node* node = findNode(pair.first);
    if (node) {
      return ft::make_pair(iterator(node), false);
    } else {
      Node* res = addNode(pair.first, pair.second);
      return ft::make_pair(iterator(res), true);
    }
  }

  iterator insertNodeWithHint(iterator hint, const value_type& val) {
    iterator res = getEndIterator();
    Node** target = NULL;

    if (hint != getBeginIterator()) {
      iterator prev = hint;
      prev--;

      if (nodeRangeComp(prev.baseNode(), hint.baseNode(), val.first) &&
          hint.baseNode()->left_ == NULL) {
        target = &(hint.baseNode()->left_);
      }
    }

    if (hint != getEndIterator() && hint.baseNode() != root_->getMaxNode()) {
      iterator next = hint;
      next++;

      if (nodeRangeComp(hint.baseNode(), next.baseNode(), val.first) &&
          hint.baseNode()->right_ == NULL) {
        target = &(hint.baseNode()->left_);
      }
    }

    if (target != NULL) {
      *target = allocateNode(val.first, val.second, hint.baseNode());
      balanceNode(hint.baseNode());
      res = iterator(*target);
    }

    return res;
  }

  iterator getBeginIterator() { return iterator(end_ptr_->getMinNode()); }

  const_iterator getBeginIterator() const {
    return const_iterator(end_ptr_->getMinNode());
  }

  iterator getEndIterator() { return iterator(end_ptr_); }

  const_iterator getEndIterator() const { return const_iterator(end_ptr_); }

  bool isEmpty() const { return root_ == NULL; }

  size_t size() const {
    size_t res = 0;
    if (!isEmpty()) res = root_->size_;
    return res;
  }

  typename NodeAllcator::size_type getMaxSize() const {
    return allocator_.max_size();
  }

  iterator findData(const Key& key) {
    Node* res = NULL;
    res = findNode(key);
    if (res == NULL)
      return iterator(end_ptr_);
    else
      return iterator(res);
  }

  const_iterator findData(const Key& key) const {
    Node* res = NULL;
    res = findNode(key);
    if (res == NULL)
      return const_iterator(end_ptr_);
    else
      return const_iterator(res);
  }

  void clearTree() {
    if (root_ == NULL) return;

    Node* featured = root_->getMinNode();
    while (featured != &end_) {
      if (featured->left_)
        featured = featured->left_;
      else if (featured->right_)
        featured = featured->right_;
      else {
        Node* tmp = featured;
        featured = featured->parent_;
        if (tmp->isRightChild()) {
          tmp->parent_->right_ = NULL;
        } else {
          tmp->parent_->left_ = NULL;
        }
        delete tmp;
      }
    }
  }

  bool deleteNode(const Key& key) {
    Node* target = findNode(key);
    if (!target) {
      return false;
    }

    Node* featured = target->parent_;

    if (target->left_) {
      Node* substitute_src = target->left_->getMaxNode();

      Node* substitute_dst = allocateNode(*substitute_src);
      target->parent_->joinNode(target->isRightChild(), substitute_dst);
      substitute_dst->joinNode(RIGHT, target->right_);
      substitute_dst->joinNode(LEFT, target->left_);

      featured = substitute_src->parent_;
      substitute_src->parent_->joinNode(substitute_src->isRightChild(),
                                        substitute_src->left_);

      delete substitute_src;
    } else if (target->right_) {
      target->parent_->joinNode(target->isRightChild(), target->right_);
    } else {
      if (target->isRightChild()) {
        target->parent_->right_ = NULL;
      } else {
        target->parent_->left_ = NULL;
      }
    }

    delete target;
    balanceNode(featured);
    return true;
  }

  Node* findLowerBoundNode(const Key& key) const {
    Node* res = NULL;
    Node* featured = root_;

    while (featured != NULL) {
      if (!featured->compare(key)) {
        res = featured;
      }
      if (featured->compare(key)) {
        featured = featured->right_;
      } else {
        featured = featured->left_;
      }
    }
    if (res == NULL) return end_ptr_;
    return res;
  }

  Node* findUpperBoundNode(const Key& key) const {
    Node* res = NULL;
    Node* featured = root_;

    while (featured != NULL) {
      if (featured->compare(key)) {
        featured = featured->right_;
      } else {
        if (!featured->equal(key)) {
          res = featured;
        }
        featured = featured->left_;
      }
    }

    if (res == NULL) return end_ptr_;
    return res;
  }

  void swap(AVLTree& x) {
    std::swap(end_, x.end_);
    root_->parent_ = end_ptr_;
    x.root_->parent_ = x.end_ptr_;
    std::swap(allocator_, x.allocator_);
    std::swap(comp_, x.comp_);
  }

 private:
  void balanceNode(Node* featured) {
    while (featured && featured != &end_) {
      featured->updateNode();
      featured = featured->parent_;
    }
  }

  Node* addNode(const Key& key, const T& value) {
    if (!root_) {
      root_ = allocateNode(key, value, &end_);
      return root_;
    }

    Node* featured = root_;
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

  Node* allocateNode(const Key& key, const T& value = T(),
                     Node* parent = NULL) {
    Node* res = NULL;

    res = allocator_.allocate(1);

    allocator_.construct(res, Node(key, value));
    res->parent_ = parent;
    return res;
  }

  Node* allocateNode(const AVLNode& src) {
    Node* res = NULL;

    res = allocator_.allocate(1);
    allocator_.construct(res, src);
    return res;
  }

  static bool nodeRangeComp(Node* first, Node* second, const Key key) {
    return first->compare(key) && Node(key).compare(second->data_.first);
  }

#ifdef DEV
 public:
  void printTreeGraph() {
    if (!root_) {
      std::cout << "root is NULL." << std::endl;
    } else {
      std::cout << "digraph sample {" << std::endl;
      root_->printTreeGraph();
      std::cout << "}" << std::endl;
    }
  }
#endif
};

}  // namespace ft

#endif /* ********************************************************* AVLTREE_H \
        */
