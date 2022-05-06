#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <limits>

#include "AVLTree.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<pair<const Key, T> > >
class map {
 private:
  typedef AVLTree<Key, T, Compare, Allocator> avl_tree;

 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef pair<const key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename avl_tree::template tree_iterator<value_type> iterator;
  typedef typename avl_tree::template tree_iterator<const value_type>
      const_iterator;
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;

  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
   protected:
    Compare comp;
    value_compare(Compare c) : comp(c) {}

   public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type& x, const value_type& y) const {
      return comp(x.first, y.first);
    }
  };

 public:
  avl_tree tree;
  allocator_type allocator_;

 public:
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
      : tree(avl_tree(comp, alloc)), allocator_(alloc) {}

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : tree(avl_tree(comp, alloc)), allocator_(alloc) {
    insert(first, last);
  };

  map(const map& src) { *this = src; };

  ~map(){};

  map& operator=(const map& rhs) {
    if (this != &rhs) {
      tree = rhs.tree;
      allocator_ = rhs.allocator_;
    }
    return *this;
  };

  allocator_type get_allocator() const { return allocator_; };

  pair<iterator, bool> insert(const value_type& value) {
    return tree.insertNode(value);
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last) {
    for (InputIt it = first; it != last; it++) {
      tree.insertNode(*it);
    }
  }

  iterator begin() { return tree.getBeginIterator(); };
  const_iterator begin() const { return tree.getBeginIterator(); };

  iterator end() { return tree.getEndIterator(); };
  const_iterator end() const { return tree.getEndIterator(); };

  reverse_iterator rbegin() { return reverse_iterator(end()); };
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  };

  reverse_iterator rend() { return reverse_iterator(begin()); };
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  };

  bool empty() const { return tree.isEmpty(); };

  size_type size() const { return tree.size(); };

  size_type max_size() const {
    return std::min<size_type>(std::numeric_limits<difference_type>::max(),
                               tree.getMaxSize());
  };

  mapped_type& operator[](const key_type& k) {
    iterator it = tree.findData(k);
    if (it == end()) {
      it = insert(ft::make_pair(k, mapped_type())).first;
    }
    return (*it).second;
  };

  iterator find(const key_type& k) { return tree.findData(k); }

  const_iterator find(const key_type& k) const { return tree.findData(k); };

  void clear() { tree.clearTree(); };

  void erase(iterator position) { tree.deleteNode((*position).first); };

  size_type erase(const key_type& k) {
    if (tree.deleteNode(k)) {
      return 1;
    }
    return 0;
  };

  void erase(iterator first, iterator last) {
    for (iterator it = first; it != last; it++) {
      erase(it);
    }
  }

  void swap(map& x) {
    std::swap(tree, x.tree);
    std::swap(allocator_, x.allocator_);
  }

  key_compare key_comp() const { return key_compare(); }

  value_compare value_comp() const { return value_compare(); }

  size_type count(const key_type& k) const {
    if (tree.findNode(k) != NULL) {
      return 1;
    }
    return 0;
  }
};

}  // namespace ft

#endif /* ************************************************************* MAP_H \
        */